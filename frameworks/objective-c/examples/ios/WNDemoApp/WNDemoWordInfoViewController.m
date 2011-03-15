/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import "WNDemoWordInfoViewController.h"
#import <Wordnik/WNAdditions.h>

/**
 * Implements a basic word lookup UI.
 */
@implementation WNDemoWordInfoViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Word Lookup";
    _client = [client retain];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {    
    WNNilRelease(_wordField);
    WNNilRelease(_lookupButton);
    WNNilRelease(_resultTextView);
    WNNilRelease(_runningIndicator);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    
    [super dealloc];
}

// from UIViewController
- (void) viewDidLoad {
    [super viewDidLoad];    
}

// from UIViewController
- (void) viewDidUnload {
    [super viewDidUnload];
    
    /* The primary view has been unloaded, so discard any subview references */
    [self discardSubviews];
}

// from UIViewController
- (void) didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


// from UIViewController
- (BOOL) shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation) interfaceOrientation {
    return YES;
}

- (void) reportError: (NSError *) error {
    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"Lookup Failure" 
                                                     message: [error localizedFailureReason]
                                                    delegate: nil 
                                           cancelButtonTitle: @"OK" 
                                            otherButtonTitles: nil] autorelease];
    [alert show];
    return;
}

- (IBAction) didPressLookupButton: (id) sender {

    /* Create our request */
    NSArray *elements = [NSArray arrayWithObjects:
                         [WNWordDefinitionRequest requestWithDictionary: [WNDictionary wordnetDictionary]],
                         [WNWordBigramRequest request],
                         [WNWordExampleRequest request],
                         [WNWordRelatedWordsRequest request],
                         [WNWordUsageFrequencyRequest request],
                         [WNWordTextPronunciationRequest request],
						 [WNAudioFileMetadataRequest request],
                         nil];
    WNWordRequest *req = [WNWordRequest requestWithWord: _wordField.text
                                         requestCanonicalForm: YES
                                   requestSpellingSuggestions: YES
                                              elementRequests: elements];
    
    /* Configure the UI */
    [_wordField resignFirstResponder];
    _wordField.enabled = NO;
    _lookupButton.enabled = NO;
    _resultTextView.text = nil;

    [_runningIndicator startAnimating];

    /* Submit */
    [_client wordWithRequest: req completionBlock: ^(WNWordResponse *response, NSError *error) {
        /* Fix up the UI */
        _wordField.enabled = YES;
        _lookupButton.enabled = YES;
        [_runningIndicator stopAnimating];
        
        /* Report error */
        if (error != nil) {
            [self reportError: error];
        }
    
        /* Populate the word info text field */
        NSMutableString *infoText = [NSMutableString string];
        WNWordObject *word = response.wordObject;

        /* Spelling suggestions */
        if ([response.spellingSuggestions count] > 0) {
            [infoText appendString: @"Did you mean: "];
            NSArray *wordStrings = [response.spellingSuggestions wn_map: ^id (id obj) {
                return [obj word];
            }];

            [infoText appendFormat: @"%@\n\n", [wordStrings componentsJoinedByString: @", "]];
        }
		
		/* Audio */
		if(word.audioFileMetadata != nil){
			[infoText appendFormat: @"Found %d audio files:\n", [word.audioFileMetadata count]];
			for(WNAudioFileMetadata * meta in word.audioFileMetadata){
				[infoText appendFormat: @"%@\n", meta.createdBy];
			}
		}

        /* Definitions */
        if (word.definitions != nil && word.definitions.count > 0) {
            [infoText appendString: @"Definitions:\n"];
            for (WNDefinitionList *list in word.definitions) {
                if (list.definitions.count == 0)
                    continue;
                
                [infoText appendFormat: @" - %@ - \n", list.sourceDictionary.localizedName];
                for (WNDefinition *def in list.definitions) {
                    [infoText appendString: @"• "];
                    
                    if (def.extendedText != nil) {
                        [infoText appendString: def.extendedText];
                    } else {
                        [infoText appendString: def.text];
                    }

                    [infoText appendString: @"\n\n"];
                }
            }
        }
        
        /* Example sentences. */
        if (word.examples != nil && word.examples.count > 0) {
            /* Create a sentence list */
            NSArray *strings = [word.examples wn_map: ^(id obj) {
                WNExample *sentence = obj;
                return [NSString stringWithFormat: @"“%@”\n%@ (%d)", 
                        sentence.text, sentence.title, [sentence.publicationDateComponents year]];
            }];
            
            [infoText appendFormat: @"Examples:\n%@", [strings componentsJoinedByString: @"\n\n"]];
        }
        
        /* Pronunciation */
        if (word.textPronunciations != nil && word.textPronunciations.count > 0) {
            NSArray *strings = [word.textPronunciations wn_map: ^(id obj) {
                WNTextPronunciation *pr = obj;
                return [NSString stringWithFormat: @"• %@: %@", pr.pronunciationType.name, pr.pronunciationString];
            }];
            
            [infoText appendFormat: @"\n\nPronunciation:\n%@", [strings componentsJoinedByString: @"\n"]];
        }
        
        /* Related words */
        if (word.relatedWords != nil && word.relatedWords.relatedWords.count > 0) {
            for (WNRelatedWordType *type in word.relatedWords.relationTypes) {
                /* Create a word list */
                NSArray *strings = [[word.relatedWords wordsForRelationType: type] wn_map: ^id (id obj) {
                    WNRelatedWordObject *relWord = obj;
                    return relWord.word;
                }];
                
                /* Append list */
                [infoText appendFormat: @"\n\n%@: %@", type.name, [strings componentsJoinedByString: @", "]];
            }
        };

        /* Bigrams */
        if (word.bigrams != nil && word.bigrams.count > 0) {
            NSArray *bigramStrings = [word.bigrams wn_map: ^(id obj) {
                WNBigram *bigram = obj;
                return [NSString stringWithFormat: @"• %@ %@", bigram.firstWordString, bigram.secondWordString];
            }];
            
            [infoText appendFormat: @"\n\nBigram Phrases:\n%@", [bigramStrings componentsJoinedByString: @"\n"]];
        }
        
        /* Usage frequency. */
        if (word.usageFrequencyTimeline != nil && word.usageFrequencyTimeline.wordFrequencies.count > 0) {
            NSArray *strings = [word.usageFrequencyTimeline.wordFrequencies wn_map: ^(id obj) {
                WNUsageFrequency *freq = obj;
                return [NSString stringWithFormat: @"• %d - %d", freq.year, freq.usageCount];
            }];
            
            [infoText appendFormat: @"\n\nUsage Frequency:\n%@", [strings componentsJoinedByString: @"\n"]];
        }

        _resultTextView.text = infoText;
    }];
}

@end
