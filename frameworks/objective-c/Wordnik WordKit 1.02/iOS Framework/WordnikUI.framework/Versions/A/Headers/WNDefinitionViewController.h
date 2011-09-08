/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>

#import <Wordnik/WNWordObject.h>
#import <Wordnik/WNWordDataSource.h>

#import <WordnikUI/WNDefinitionView.h>
#import <WordnikUI/WNDefinitionViewControllerDelegate.h>

@interface WNDefinitionViewController : UIViewController {
@private
    /** The displayed definition view. */
    WNDefinitionView *_definitionView;
    
    /** Network activity spinner. */
    UIActivityIndicatorView *_activityIndicator;
    
    /** "Did you mean?" table. Will be nil if no suggestions. */
    UITableView *_suggestionTable;
    
    /** Error container. Holds the two error labels. */
    UIView *_errorContainer;

    /** Error message label. */
    UILabel *_errorLabel;

    /** Error message. */
    UILabel *_errorMessage;

    /** If YES, ignore any spelling suggestions. */
    BOOL _ignoreSuggestions;

    /** If YES, lookup pending. */
    BOOL _isBusy;

    /** The word string to be looked up. */
    NSString *_word;
    
    /** The word response, or nil if not yet received. */
    WNWordResponse *_wordResponse;

    /** Non-retained data source. */
    id<WNWordDataSource> _dataSource;

    /** Non-retained delegate. */
    id<WNDefinitionViewControllerDelegate> _delegate;

    /** A sub-definition view controller, if any. Will be nil if a new word view controller
     * has not been pushed onto the navigation view stack. */
    WNDefinitionViewController *_subcontroller;
}

- (id) initWithWord: (NSString *) word dataSource: (id<WNWordDataSource>) dataSource;

/** The object that acts as the data source of the receiving definition view controller. */
@property(nonatomic, assign) id<WNWordDataSource> dataSource;

/** The view controller delegate. */
@property(nonatomic, assign) id<WNDefinitionViewControllerDelegate> delegate;

@end
