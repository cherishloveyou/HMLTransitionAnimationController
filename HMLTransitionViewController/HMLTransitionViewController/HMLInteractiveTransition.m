/**
// Copyright (c) 2014 huamulou. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
* //                       _oo0oo_
* //                      o8888888o
* //                      88" . "88
* //                      (| -_- |)
* //                      0\  =  /0
* //                    ___/`---'\___
* //                  .' \\|     |// '.
* //                 / \\|||  :  |||// \
* //                / _||||| -:- |||||- \
* //               |   | \\\  -  /// |   |
* //               | \_|  ''\---/''  |_/ |
* //               \  .-\__  '-'  ___/-. /
* //             ___'. .'  /--.--\  `. .'___
* //          ."" '<  `.___\_<|>_/___.' >' "".
* //         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
* //         \  \ `_.   \_ __\ /__ _/   .-` /  /
* //     =====`-.____`.___ \_____/___.-`___.-'=====
* //                       `=---='
* //     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* //
* //               佛祖保佑         永无BUG
*/


//

#import "HMLInteractiveTransition.h"
#import "HMLTransitionViewController.h"


@interface HMLInteractiveTransition () {
}

@property(nonatomic, assign) HMLTransitionViewController *transitionViewController;
@property(nonatomic, assign) CGFloat fullWidth;
@property(nonatomic, assign) CGFloat fullHeight;

@property(nonatomic, assign) HMLTransitionAnchoredDirection positiveDirection;

@property(nonatomic, assign) CGFloat currentPercentage;
@property(nonatomic, copy) void (^coordinatorInteractionEnded)(id <UIViewControllerTransitionCoordinatorContext> context);
@end

@implementation HMLInteractiveTransition {

}


#pragma mark - Constructors

- (id)initWithTransitionViewController:(HMLTransitionViewController *)transitionViewController {
    self = [super init];
    if (self) {
        self.transitionViewController = transitionViewController;
    }

    return self;
}

#pragma mark - UIViewControllerInteractiveTransitioning

- (void)startInteractiveTransition:(id <UIViewControllerContextTransitioning>)transitionContext {
    [super startInteractiveTransition:transitionContext];

    CGFloat fullWidth = _transitionViewController.view.frame.size.width;
    CGFloat fullHeight = _transitionViewController.view.frame.size.height;

    self.fullWidth = fullWidth;
    self.fullHeight = fullHeight;
    self.currentPercentage = 0;
}

#pragma mark - UIPanGestureRecognizer action

- (void)updateTopViewHorizontalCenterWithRecognizer:(UIPanGestureRecognizer *)recognizer {
    CGFloat velocityX = [recognizer velocityInView:self.transitionViewController.view].x;
    CGFloat velocityY = [recognizer velocityInView:self.transitionViewController.view].y;

    switch (recognizer.state) {
        case UIGestureRecognizerStateBegan: {
            HMLTransitionAnchoredDirection toNext = self.transitionViewController.toNextDirection;
            HMLTransitionAnchoredDirection toPre = self.transitionViewController.toPreDirection;
            if (toNext && toNext & HMLTransitionAnchoredUp && velocityY < 0) {
                [self.transitionViewController transitionToNextView:YES];
                _positiveDirection = HMLTransitionAnchoredUp;
            } else if (toNext && toNext & HMLTransitionAnchoredDown && velocityY > 0) {
                [self.transitionViewController transitionToNextView:YES];
                _positiveDirection = HMLTransitionAnchoredDown;
            } else if (toNext && toNext & HMLTransitionAnchoredLeft && velocityX < 0) {
                [self.transitionViewController transitionToNextView:YES];
                _positiveDirection = HMLTransitionAnchoredLeft;
            } else if (toNext && toNext & HMLTransitionAnchoredRight && velocityX > 0) {
                [self.transitionViewController transitionToNextView:YES];
                _positiveDirection = HMLTransitionAnchoredRight;
            } else if (toPre && toPre & HMLTransitionAnchoredUp && velocityY < 0) {
                [self.transitionViewController transitionToPreView:YES];
                _positiveDirection = HMLTransitionAnchoredUp;
            } else if (toPre && toPre & HMLTransitionAnchoredDown && velocityY > 0) {
                [self.transitionViewController transitionToPreView:YES];
                _positiveDirection = HMLTransitionAnchoredDown;
            } else if (toPre && toPre & HMLTransitionAnchoredLeft && velocityX < 0) {
                [self.transitionViewController transitionToPreView:YES];
                _positiveDirection = HMLTransitionAnchoredLeft;
            } else if (toPre && toPre & HMLTransitionAnchoredRight && velocityX > 0) {
                [self.transitionViewController transitionToPreView:YES];
                _positiveDirection = HMLTransitionAnchoredRight;
            }


            break;
        }
        case UIGestureRecognizerStateChanged: {
            CGFloat percentComplete = [self getPercentCompleteByTranslation:[recognizer translationInView:self.transitionViewController.view]];
            if (percentComplete < 0) percentComplete = 0;
            [self updateInteractiveTransition:percentComplete];
            break;
        }
        case UIGestureRecognizerStateEnded:
        case UIGestureRecognizerStateCancelled: {
            BOOL isFinish = [self isFinishByTranslationInView:[recognizer translationInView:self.transitionViewController.view] velocityInView:[recognizer velocityInView:self.transitionViewController.view]];

            if (self.coordinatorInteractionEnded) self.coordinatorInteractionEnded((id <UIViewControllerTransitionCoordinatorContext>) self.transitionViewController);

            if (isFinish) {
                [self finishInteractiveTransition];
            } else {
                [self cancelInteractiveTransition];
            }

            break;
        }
        default:
            break;
    }
}


- (CGFloat)getPercentCompleteByTranslation:(CGPoint)translationInView {

    if (_positiveDirection == HMLTransitionAnchoredUp || _positiveDirection == HMLTransitionAnchoredDown) {
        return fabs(translationInView.y) / _fullHeight;
    } else {
        return fabs(translationInView.y) / _fullWidth;
    }
}

- (CGFloat)isFinishByTranslationInView:(CGPoint)translationInView velocityInView:(CGPoint)velocityInView {

    if (_positiveDirection == HMLTransitionAnchoredUp && velocityInView.y < 0) {
        return YES;
    } else if (_positiveDirection == HMLTransitionAnchoredDown && velocityInView.y > 0) {
        return YES;
    } else if (_positiveDirection == HMLTransitionAnchoredLeft && velocityInView.x < 0) {
        return YES;
    } else if (_positiveDirection == HMLTransitionAnchoredRight && velocityInView.x > 0) {
        return YES;
    }
    return NO;
}


@end