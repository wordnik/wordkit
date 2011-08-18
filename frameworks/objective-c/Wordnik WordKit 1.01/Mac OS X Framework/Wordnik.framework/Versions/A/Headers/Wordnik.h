/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * @defgroup classes Class Reference
 */

/**
 * @internal
 * @ingroup classes
 * @defgroup internal_api Wordnik Internal
 *
 * A set of private APIs that are accessible to other Wordnik libraries.
 */

/**
 * @ingroup classes
 * @defgroup classes_data Word Data
 *
 * Wordnik data classes.
 */

/**
 * @defgroup constants Constants Reference
 */

/**
 * @defgroup enums Enumerations
 * @ingroup constants
 */

/**
 * @defgroup globals Global Variables
 * @ingroup constants
 */

/**
 * @defgroup exceptions Exceptions
 * @ingroup constants
 */


/* Library Imports */
#import <Wordnik/WNConstants.h>
#import <Wordnik/WNClient.h>
#import <Wordnik/WNWordObject.h>

#import <Wordnik/WNWordDataSource.h>
#import <Wordnik/WNWordNetworkDataSource.h>

/**
 * @mainpage Wordnik Data SDK
 *
 * @section intro_sec Introduction
 *
 * The Wordnik Objective C Data and WordKit SDKs provide common APIs for accessing Wordnik's data from iOS and Mac OS X
 * applications.
 *
 *
 * You'll need a valid Wordnik API Key to use these libraries.  Please visit <a href="http://developer.wordnik.com">http://developer.wordnik.com</a> 
 * to sign up for an API Key.  You should also visit our documentation at <a href="http://developer.wordnik.com/docs">http://developer.wordnik.com/docs</a>
 * to see the details of how the APIs work.  While in most cases, the iOS SDKs will abstract the underlying Wordnik API from you, it's
 * important to understand what is happening across the API.
 * 
 * Our most up-to-date documentation can be found at <a href="http://developer.wordnik.com/libraries/objective-c-sdk">http://developer.wordnik.com/libraries/objective-c-sdk</a> which
 * provides code samples and recipes for using the SDK.
 * 
 * 
 * @section doc_sections Documentation Sections
 * - @subpage error_handling
 * 
 * 
 */


/**
 * @page error_handling Error Handling Programming Guide
 *
 * Where a method may return an error, Wordnik provides access to the underlying cause via an
 * optional NSError argument.
 *
 * All returned errors will be a member of one of the below defined domains, however, new domains and
 * error codes may be added at any time. If you do not wish to report on the error cause, many methods
 * support a simple form that requires no NSError argument.
 *
 * @section Error Domains, Codes, and User Info
 *
 * @subsection error_domains Errors
 *
 * Any errors in Wordnik use the #WNErrorDomain error domain, and and one
 * of the error codes defined in #WNErrorCode.
 */
