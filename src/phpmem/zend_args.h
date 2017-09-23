#pragma once
#include "phpmem.h"

ZEND_BEGIN_ARG_INFO_EX(AI_None, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_String, 0, 0, 1)
ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_Long, 0, 0, 1)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongLong, 0, 0, 2)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongLongLong, 0, 0, 3)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongLongLongLong, 0, 0, 4)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongAnyLong, 0, 0, 3)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, any)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongLongAnyLong, 0, 0, 4)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, any)
ZEND_ARG_INFO(0, num)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(AI_LongString, 0, 0, 2)
ZEND_ARG_INFO(0, num)
ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()