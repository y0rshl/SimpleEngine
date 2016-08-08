//
//  SharedStructures.h
//  osx
//
//  Created by SANDSTORM04 on 7/23/16.
//  Copyright (c) 2016 ITBA. All rights reserved.
//

#ifndef SharedStructures_h
#define SharedStructures_h

#include <simd/simd.h>

typedef struct __attribute__((__aligned__(256)))
{
    matrix_float4x4 modelview_projection_matrix;
    matrix_float4x4 normal_matrix;
} uniforms_t;

#endif /* SharedStructures_h */

