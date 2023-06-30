/*
 * MedianFilter.h
 *
 *  Created on: May 19, 2018
 *      Author: alexandru.bogdan
 *  Modified on: June 30, 2023
 *      Author: I_AM_ENGINEER
 */

#include <stdint.h>

#ifndef MEDIANFILTER_H_
#define MEDIANFILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MEDIAN_STATE_OK			= 0,
	MEDIAN_STATE_ERROR	= -1,
} median_state_t;

typedef struct median_node_i32 {
	int32_t value;											//sample value
	struct median_node_i32 *next_age;		//pointer to next oldest value
	struct median_node_i32 *next_value;	//pointer to next smallest value
	struct median_node_i32 *prev_value;	//pointer to previous smallest value
} median_node_i32_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_i32_t *median_buffer;		//median node buffer
	median_node_i32_t *age_head;				//pointer to oldest value
	median_node_i32_t *value_head;			//pointer to smallest value
	median_node_i32_t *median_head;			//pointer to median value
} median_filter_i32_t;


typedef struct median_node_u32 {
	uint32_t value;											//sample value
	struct median_node_u32 *next_age;		//pointer to next oldest value
	struct median_node_u32 *next_value;	//pointer to next smallest value
	struct median_node_u32 *prev_value;	//pointer to previous smallest value
} median_node_u32_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_u32_t *median_buffer;		//median node buffer
	median_node_u32_t *age_head;				//pointer to oldest value
	median_node_u32_t *value_head;			//pointer to smallest value
	median_node_u32_t *median_head;			//pointer to median value
} median_filter_u32_t;


typedef struct median_node_i16 {
	int16_t value;											//sample value
	struct median_node_i16 *next_age;		//pointer to next oldest value
	struct median_node_i16 *next_value;	//pointer to next smallest value
	struct median_node_i16 *prev_value;	//pointer to previous smallest value
} median_node_i16_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_i16_t *median_buffer;		//median node buffer
	median_node_i16_t *age_head;				//pointer to oldest value
	median_node_i16_t *value_head;			//pointer to smallest value
	median_node_i16_t *median_head;			//pointer to median value
} median_filter_i16_t;


typedef struct median_node_u16 {
	uint16_t value;											//sample value
	struct median_node_u16 *next_age;		//pointer to next oldest value
	struct median_node_u16 *next_value;	//pointer to next smallest value
	struct median_node_u16 *prev_value;	//pointer to previous smallest value
} median_node_u16_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_u16_t *median_buffer;		//median node buffer
	median_node_u16_t *age_head;				//pointer to oldest value
	median_node_u16_t *value_head;			//pointer to smallest value
	median_node_u16_t *median_head;			//pointer to median value
} median_filter_u16_t;


typedef struct median_node_i8 {
	int8_t value;												//sample value
	struct median_node_i8 *next_age;		//pointer to next oldest value
	struct median_node_i8 *next_value;	//pointer to next smallest value
	struct median_node_i8 *prev_value;	//pointer to previous smallest value
} median_node_i8_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_i8_t *median_buffer;		//median node buffer
	median_node_i8_t *age_head;					//pointer to oldest value
	median_node_i8_t *value_head;				//pointer to smallest value
	median_node_i8_t *median_head;			//pointer to median value
} median_filter_i8_t;


typedef struct median_node_u8 {
	uint8_t value;											//sample value
	struct median_node_u8 *next_age;		//pointer to next oldest value
	struct median_node_u8 *next_value;	//pointer to next smallest value
	struct median_node_u8 *prev_value;	//pointer to previous smallest value
} median_node_u8_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_u8_t *median_buffer;		//median node buffer
	median_node_u8_t *age_head;					//pointer to oldest value
	median_node_u8_t *value_head;				//pointer to smallest value
	median_node_u8_t *median_head;			//pointer to median value
} median_filter_u8_t;


typedef struct median_node_f {
	float value;												//sample value
	struct median_node_f *next_age;			//pointer to next oldest value
	struct median_node_f *next_value;		//pointer to next smallest value
	struct median_node_f *prev_value;		//pointer to previous smallest value
} median_node_f_t;

typedef struct {
	unsigned int num_nodes;							//median node buffer length
	median_node_f_t *median_buffer;			//median node buffer
	median_node_f_t *age_head;					//pointer to oldest value
	median_node_f_t *value_head;				//pointer to smallest value
	median_node_f_t *median_head;				//pointer to median value
} median_filter_f_t;


/**
  * @brief  This function initializes filter's data structure
	* @param  filter : Data structure
  * @retval State of initialization
  */
median_state_t median_init_i32( median_filter_i32_t *median_filter, median_node_i32_t* nodes, unsigned int nodes_count, int32_t  default_value );
median_state_t median_init_i16( median_filter_i16_t *median_filter, median_node_i16_t* nodes, unsigned int nodes_count, int16_t  default_value );
median_state_t median_init_i8 ( median_filter_i8_t  *median_filter, median_node_i8_t*  nodes, unsigned int nodes_count, int8_t   default_value );
median_state_t median_init_u32( median_filter_u32_t *median_filter, median_node_u32_t* nodes, unsigned int nodes_count, uint32_t default_value );
median_state_t median_init_u16( median_filter_u16_t *median_filter, median_node_u16_t* nodes, unsigned int nodes_count, uint16_t default_value );
median_state_t median_init_u8 ( median_filter_u8_t  *median_filter, median_node_u8_t*  nodes, unsigned int nodes_count, uint8_t  default_value );
median_state_t median_init_f  ( median_filter_f_t   *median_filter, median_node_f_t*   nodes, unsigned int nodes_count, float    default_value );

/**
  * @brief  This function filters data with moving average filter
	* @param  filter : Data structure
	* @param  value : value for insert to buffer
  * @retval None
  */
int32_t  median_insert_i32( median_filter_i32_t *median_filter, int32_t  value );
int16_t  median_insert_i16( median_filter_i16_t *median_filter, int16_t  value );
int8_t   median_insert_i8 ( median_filter_i8_t  *median_filter, int8_t   value );
uint32_t median_insert_u32( median_filter_u32_t *median_filter, uint32_t value );
uint16_t median_insert_u16( median_filter_u16_t *median_filter, uint16_t value );
uint8_t  median_insert_u8 ( median_filter_u8_t  *median_filter, uint8_t  value );
float    median_insert_f  ( median_filter_f_t   *median_filter, float    value );

/**
  * @brief  This function return filtered value
  * @param  filter : Data structure
  * @retval Filtered value
  */
int32_t  median_get_i32( median_filter_i32_t *median_filter );
int16_t  median_get_i16( median_filter_i16_t *median_filter );
int8_t   median_get_i8 ( median_filter_i8_t  *median_filter );
uint32_t median_get_u32( median_filter_u32_t *median_filter );
uint16_t median_get_u16( median_filter_u16_t *median_filter );
uint8_t  median_get_u8 ( median_filter_u8_t  *median_filter );
float   median_get_f  ( median_filter_f_t   *median_filter );
#ifdef __cplusplus
}
#endif
#endif
