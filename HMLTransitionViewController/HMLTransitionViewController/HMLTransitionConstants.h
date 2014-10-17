//
//  HMLTransitionConstants.h
//  HMLTransitionViewController
//
//  Created by huamulou on 14-10-15.
//  Copyright (c) 2014年 showmethemoney. All rights reserved.
//



#define HML_IOS_SYS_VERSION [UIDevice currentDevice].systemVersion.floatValue

#define HML_IOS7_PLUS (HML_IOS_SYS_VERSION >= 7.0f)

#ifndef ECSlidingViewController_ECSlidingConstants_h
#define ECSlidingViewController_ECSlidingConstants_h


/**
* 中间view key
*/
static NSString *const HMLTransitionContextTopViewControllerKey = @"HMLTransitionContextTopViewControllerKey";

/**
* 上一个view key
*/
static NSString *const HMLTransitionContextPreViewControllerKey = @"HMLTransitionContextPreViewControllerKey";

/**
* 下一个view key
*/
static NSString *const HMLTransitionContextNextViewControllerKey = @"HMLTransitionContextNextViewControllerKey";


static NSString *const HMLTransitionContextToViewControllerKey = @"HMLTransitionContextToViewControllerKey";


static NSString *const HMLTransitionContextViewTobeAdd = @"HMLTransitionContextViewTobeAdd";
static NSString *const HMLTransitionContextViewTobeDelete = @"HMLTransitionContextViewTobeDelete";


typedef NS_ENUM(NSInteger, HMLTransitionViewControllerOperation) {
    /**
    * 没有改变
    */
            HMLTransitionViewControllerOperationNone,
    //切换到上一个view
            HMLTransitionViewControllerOperation2Pre,

    //切换到下一个view
            HMLTransitionViewControllerOperation2Next
};

/**
变换的过程
*/
typedef NS_ENUM(NSInteger, HMLTransitionViewControllerAnchor) {
    /**
    * 没有改变
    */
            HMLTransitionViewControllerAnchorNone,
    /**
    * 向左滑动
    */
            HMLTransitionViewControllerAnchorLeft,
    /**
    * 向右
    */
            HMLTransitionViewControllerAnchorRight,
    /**
    * 左回
    */
            HMLTransitionViewControllerResetFromLeft,
    /**
    * 右回
    */
            HMLTransitionViewControllerResetFromRight,
    /**
    * 向上
    */
            HMLTransitionViewControllerAnchorUp,

    /**
    * 上回
    */
            HMLTransitionViewControllerResetFromUp,
    /**
    * 向上
    */

            HMLTransitionViewControllerAnchorDown,

    /**
    * 上回
    */

            HMLTransitionViewControllerResetFromDown
};


/**
* 可以变换的方向
*/
typedef NS_ENUM(NSInteger, HMLTransitionAnchoredDirection) {

    //向上
            HMLTransitionAnchoredUp = 1 << 0,
    //向下
            HMLTransitionAnchoredDown = 1 << 1,
    //向左
            HMLTransitionAnchoredLeft = 1 << 2,
    //向右
            HMLTransitionAnchoredRight = 1 << 3

};


/**
Options for gestures/behaviors given to a top view while it is anchored to the left or right.

All the options except `ECSlidingViewControllerAnchoredGestureNone` will create a transparent view that is placed above the top view when it is anchored. This transparent view will block all gestures that are on the top view. Choose a combination of `ECSlidingViewControllerAnchoredGesturePanning`, `ECSlidingViewControllerAnchoredGestureTapping`, and `ECSlidingViewControllerAnchoredGestureCustom` to temporarily add gestures to the transparent view.
*/
typedef NS_OPTIONS(NSInteger, HMLTransitionViewControllerAnchoredGesture) {
    /** Nothing is done to the top view while it is anchored. */
            HMLTransitionViewControllerAnchoredGestureNone = 0,
    /** The sliding view controller's `panGesture` is made available while the top view is anchored. This option is only relevant for transitions that use the default interactive transition. It is also only used if the sliding view controller's `panGesture` is enabled and added to a view. */
            HMLTransitionViewControllerAnchoredGesturePanning = 1 << 0,
    /** The sliding view controller's `resetTapGesture` is made available while the top view is anchored. */
            HMLTransitionViewControllerAnchoredGestureTapping = 1 << 1,
    /** Any gestures set on the sliding view controller's `customAnchoredGestures` property are made available while the top view is anchored. These gestures are temporarily removed from their current view. */
            HMLTransitionViewControllerAnchoredGestureCustom = 1 << 2,
    /** All user interactions on the top view are disabled when anchored. This takes precedence when combined with any other option. */
            HMLTransitionViewControllerAnchoredGestureDisabled = 1 << 3
};


#endif


