/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>

#import <Wordnik/WNWordObject.h>
#import <WordnikUI/WNDefinitionViewDelegate.h>

#ifdef WORDNIK_PRIVATE
#import "WNBoxVerticalLayoutNode.h"
#import "WNDefinitionFontFamily.h"
#import "WNDefinitionHeaderView.h"
#else
@class WNBoxVerticalLayoutNode;
@class WNDefinitionFontFamily;
@class WNDefinitionHeaderView;
#endif /* WORDNIK_PRIVATE */

@class WNDefinitionScrollView;
@class WNDefinitionViewDelegateReference;

@interface WNDefinitionView : UIView {
@private
    /** The displayed word. */
    WNWordObject *_word;
    
    /** The "powered by:" label to the right of the logo */
    UILabel *_poweredByLabel;
    
    /** The branding logo image view, upper left corner */
    UIImageView *_poweredByView;
    
    /** The word label. Fixed and displayed at the top of the view. */
    UILabel *_wordLabel;

    /** The section quick-link header */
    WNDefinitionHeaderView *_headerView;

    /** Our embedded scroll view */
    WNDefinitionScrollView *_scrollView;
    
    /** If YES, scroll view is being scrolled automatically to a specific point, ie, not by the user. */
    BOOL _nonUserScrolling;
    
    /** Definition sections displayed within the scroll view. */
    NSArray *_sections;

    /** The box layout heirarchy. */
    WNBoxVerticalLayoutNode *_boxNode;

    /** Font family to use for rendering. */
    WNDefinitionFontFamily *_fontFamily;

    /** Delegate reference */
    WNDefinitionViewDelegateReference *_delegateRef;
}

- (id) initWithFrame: (CGRect) frame;

/** The displayed word, or nil if none configured. The definition will be derived from this word record. */
@property(nonatomic, retain) WNWordObject *word;

/** The definition view delegate. The del*/
@property(nonatomic, assign) id<WNDefinitionViewDelegate> delegate;

@end
