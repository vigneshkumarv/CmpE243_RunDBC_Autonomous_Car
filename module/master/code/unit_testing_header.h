/*
 * unit_testing_header.h
 *
 *  Created on: Mar 24, 2019
 *      Author: reldn_000
 */

#ifndef UNIT_TESTING_HEADER_H_
#define UNIT_TESTING_HEADER_H_

#ifdef UNIT_TESTING
  #define static /* blank */
#else
  #define static static
#endif

#endif /* UNIT_TESTING_HEADER_H_ */
