//
//  WNAdditions.h
//  WNDemoApp
//
//  Created by Tony Tam on 3/15/11.
//  Copyright 2011 wordnik. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @ingroup additions_foundation
 *
 * Release the provided object and set its pointer value to nil.
 *
 * @param obj Object pointer to release and set to nil.
 */
#define WNNilRelease(obj) {\
[obj release]; \
obj = nil; \
}
