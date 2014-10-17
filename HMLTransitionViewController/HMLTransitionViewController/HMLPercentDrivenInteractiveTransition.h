/**
* TODO 如果没有注释 那么你懂的
* User: huamulou
* Date: 14-10-16
* Time: 11:13
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

// Copyright (c) 2014 showmethemoney. All rights reserved.
//
/**
* 通过百分比来驱动切换的工具类
*/

#import <Foundation/Foundation.h>


@interface HMLPercentDrivenInteractiveTransition : NSObject <UIViewControllerInteractiveTransitioning>
/**
The animator object that will be percent-driven.
The animation will be triggered when the interactive transition is triggered,
but instead of playing from start to finish it will be controlled by the calls to `updateInteractiveTransition:`, `cancelInteractiveTransition`, and `finishInteractiveTransition`.

返回动画的控制类
*/
@property(nonatomic, strong) id <UIViewControllerAnimatedTransitioning> animationController;

/**
The amount of the transition (specified as a percentage of the overall duration) that is complete.

The value in this property reflects the last value passed to the `updateInteractiveTransition:` method.

标识动画完成的百分比，是最后被传递到updateInteractiveTransition方法的值
*/
@property(nonatomic, assign, readonly) CGFloat percentComplete;

/**
Updates the completion percentage of the transition.
In general terms, this method is used to "scrub the playhead" of the animation defined by the `animationController`.

While tracking user events, your code should call this method regularly to update the current progress toward completing the transition.
If, during tracking, the interactions cross a threshold that you consider signifies the completion or cancellation of the transition,
stop tracking events and call the finishInteractiveTransition or cancelInteractiveTransition method.

更新动画的百分比，通常用于更新动画的起始点
*/
- (void)updateInteractiveTransition:(CGFloat)percentComplete;

/**
Causes the animation defined by the `animationController` to play from current `percentComplete` to zero percent.
You must call this method or `finishInteractiveTransition` at some point during the interaction to ensure everything ends in a consistent state.

把动画调整到头部，退出交互
*/
- (void)cancelInteractiveTransition;

/**
Causes the animation defined by the `animationController` to play from current `percentComplete` to 100 percent.
You must call this method or `cancelInteractiveTransition` at some point during the interaction to ensure everything ends in a consistent state.

把动画播放到尾部，结束交互
*/
- (void)finishInteractiveTransition;

@end