//
//  HMLTransitionViewController.h
//  HMLTransitionViewController
//
//  Created by huamulou on 14-10-15.
//  Copyright (c) 2014年 showmethemoney. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "HMLTransitionConstants.h"

@protocol HMLTansitionViewControllerDelegate;
@protocol HMLTansitionViewControllerDataSource;


@interface HMLTransitionViewController : UIViewController <UIViewControllerContextTransitioning,
        UIViewControllerTransitionCoordinator,
        UIViewControllerTransitionCoordinatorContext> {

@private
    UIPanGestureRecognizer *_panGesture;
}


/**
* 上一个view
*/
@property(nonatomic, strong) UIViewController *preViewController;

/**
* 目前的view
*/
@property(nonatomic, strong) UIViewController *topViewController;

/**
* 下一个view
*/
@property(nonatomic, strong) UIViewController *nextViewController;


+ (instancetype)initWithTopViewController:(UIViewController *)preViewController preViewController:(UIViewController *)topViewController nextViewController:(UIViewController *)nextViewController;


@property(nonatomic, assign) HMLTransitionAnchoredDirection toNextDirection;
@property(nonatomic, assign) HMLTransitionAnchoredDirection toPreDirection;

/**
The gesture that triggers the default interactive transition for a horizontal swipe. This is typically added to the top view or one of the top view's subviews.
*/
@property(nonatomic, strong, readonly) UIPanGestureRecognizer *panGesture;


/**
The default duration of the view transition.
*/
@property(nonatomic, assign) NSTimeInterval defaultTransitionDuration;


- (void)transitionToPreView:(BOOL)animated;

- (void)transitionToNextView:(BOOL)animated;


- (void)transitionToPreView:(BOOL)animated  onComplete:(void (^)())complete;

- (void)transitionToNextView:(BOOL)animated  onComplete:(void (^)())complete;


/**
The delegate that provides objects to customizing the transition animation, transition interaction, or layout of the child view controllers. See the `ECSlidingViewControllerDelegate` protocol for more information.
*/
@property(nonatomic, assign) id <HMLTansitionViewControllerDelegate> delegate;


@property(nonatomic, assign) id <HMLTansitionViewControllerDataSource> dataSource;

@end


/**
The `HMLTansitionViewControllerDelegate` protocol is adopted by an object that may customize a sliding view controller's animation transition,
interactive transition, or the layout of the child views.
*/
@protocol HMLTansitionViewControllerDelegate <NSObject>

@optional
/**
Called to allow the delegate to return a non-interactive animator object for use during a transition.

Returning an object will disable the sliding view controller's `transitionCoordinator` animation and completion callbacks.

@param slidingViewController The sliding view controller that is being transitioned.
@param operation The type of transition that is occuring. See `ECSlidingViewControllerOperation` for a list of possible values.
@param topViewController

@return The animator object responsible for managing the transition animations, or nil if you want to use the standard sliding view controller transitions. The object you return must conform to the `UIViewControllerAnimatedTransitioning` protocol.
*/
- (id <UIViewControllerAnimatedTransitioning>)transitionViewController:(HMLTransitionViewController *)transitionViewController
                                       animationControllerForOperation:(HMLTransitionViewControllerOperation)operation
                                                     topViewController:(UIViewController *)topViewController;

/**
Called to allow the delegate to return an interactive animator object for use during a transition.

Returning an object will disable the sliding view controller's `transitionCoordinator` block given to `notifyWhenInteractionEndsUsingBlock:`

@param slidingViewController The sliding view controller that is being transitioned.
@param animationController The non-interactive animator object. This will be the same object that is returned from `slidingViewController:animationController:topViewController`.

@return The animator object responsible for managing the interactive transition, or nil if you want to use the standard sliding view controller transitions. The object you return must conform to the `UIViewControllerInteractiveTransitioning` protocol.
*/
- (id <UIViewControllerInteractiveTransitioning>)transitionViewController:(HMLTransitionViewController *)transitionViewController
                              interactionControllerForAnimationController:(id <UIViewControllerAnimatedTransitioning>)animationController;


@end


/**
* 一个获取viewController的代理
*/
@protocol HMLTansitionViewControllerDataSource <NSObject>

/**
* 通过操作来获取
*/
- (UIViewController *)fetchByOperation:(HMLTransitionViewControllerOperation)operation currentViewController:(UIViewController *)currentViewController;
@end



