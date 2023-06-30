/*
 * median_filter.c
 *
 *  Created on: May 19, 2018
 *      Author: alexandru.bogdan
 *  Modified on: June 30, 2023
 *      Author: I_AM_ENGINEER
 */

#include <stddef.h>
#include "median_filter.h"

/******************************* int32 ****************************************/

median_state_t median_init_i32( median_filter_i32_t *median_filter, median_node_i32_t* nodes, unsigned int nodes_count, int32_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

int32_t median_insert_i32( median_filter_i32_t *median_filter, int32_t value ) {
	unsigned int i;

	median_node_i32_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_i32(median_filter);
}

int32_t median_get_i32( median_filter_i32_t *median_filter ) {
	return median_filter->median_head->value;
}

/******************************* uint32 ****************************************/

median_state_t median_init_u32( median_filter_u32_t *median_filter, median_node_u32_t* nodes, unsigned int nodes_count, uint32_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

uint32_t median_insert_u32( median_filter_u32_t *median_filter, uint32_t value ) {
	unsigned int i;

	median_node_u32_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_u32(median_filter);
}

uint32_t median_get_u32( median_filter_u32_t *median_filter ) {
	return median_filter->median_head->value;
}

/******************************* int16 ****************************************/

median_state_t median_init_i16( median_filter_i16_t *median_filter, median_node_i16_t* nodes, unsigned int nodes_count, int16_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

int16_t median_insert_i16( median_filter_i16_t *median_filter, int16_t value ) {
	unsigned int i;

	median_node_i16_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_i16(median_filter);
}

int16_t median_get_i16( median_filter_i16_t *median_filter ) {
	return median_filter->median_head->value;
}

/******************************* uint16 ****************************************/

median_state_t median_init_u16( median_filter_u16_t *median_filter, median_node_u16_t* nodes, unsigned int nodes_count, uint16_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

uint16_t median_insert_u16( median_filter_u16_t *median_filter, uint16_t value ) {
	unsigned int i;

	median_node_u16_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_u16(median_filter);
}

uint16_t median_get_u16( median_filter_u16_t *median_filter ) {
	return median_filter->median_head->value;
}


/******************************* int8 ****************************************/

median_state_t median_init_i8( median_filter_i8_t *median_filter, median_node_i8_t* nodes, unsigned int nodes_count, int8_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

int8_t median_insert_i8( median_filter_i8_t *median_filter, int8_t value ) {
	unsigned int i;

	median_node_i8_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_i8(median_filter);
}

int8_t median_get_i8( median_filter_i8_t *median_filter ) {
	return median_filter->median_head->value;
}

/******************************* uint8 ****************************************/

median_state_t median_init_u8( median_filter_u8_t *median_filter, median_node_u8_t* nodes, unsigned int nodes_count, uint8_t default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

uint8_t median_insert_u8( median_filter_u8_t *median_filter, uint8_t value ) {
	unsigned int i;

	median_node_u8_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_u8(median_filter);
}

uint8_t median_get_u8( median_filter_u8_t *median_filter ) {
	return median_filter->median_head->value;
}

/******************************* float ****************************************/

median_state_t median_init_f( median_filter_f_t *median_filter, median_node_f_t* nodes, unsigned int nodes_count, float default_value ){
	if(median_filter == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes == NULL){
		return MEDIAN_STATE_ERROR;
	}
	if((nodes_count % 2) == 0){
		return MEDIAN_STATE_ERROR;
	}
	if(nodes_count == 0){
		return MEDIAN_STATE_ERROR;
	}

	median_filter->median_buffer = nodes;
	median_filter->num_nodes = nodes_count;

	//initialize buffer nodes
	for(unsigned int i = 0; i < median_filter->num_nodes; i++){
		median_filter->median_buffer[i].value = default_value;
		median_filter->median_buffer[i].next_age = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[i].next_value = &median_filter->median_buffer[(i + 1) % median_filter->num_nodes];
		median_filter->median_buffer[(i + 1) % median_filter->num_nodes].prev_value = &median_filter->median_buffer[i];
	}
	//initialize heads
	median_filter->age_head = median_filter->median_buffer;
	median_filter->value_head = median_filter->median_buffer;
	median_filter->median_head = &median_filter->median_buffer[median_filter->num_nodes / 2];
	return MEDIAN_STATE_OK;
}

float median_insert_f( median_filter_f_t *median_filter, float value ) {
	unsigned int i;

	median_node_f_t *new_node, *it;

	if(median_filter->age_head == median_filter->value_head){
		//if oldest node is also the smallest node, increment value head
		median_filter->value_head = median_filter->value_head->next_value;
	}

	if((median_filter->age_head == median_filter->median_head) ||
		(median_filter->age_head->value > median_filter->median_head->value))
	{   //prepare for median correction
		median_filter->median_head = median_filter->median_head->prev_value;
	}

	//replace age head with new sample
	new_node = median_filter->age_head;
	new_node->value = value;

	//remove age head from list
	median_filter->age_head->next_value->prev_value = median_filter->age_head->prev_value;
	median_filter->age_head->prev_value->next_value = median_filter->age_head->next_value;
	//increment age head
	median_filter->age_head = median_filter->age_head->next_age;

	//find new node position
	it = median_filter->value_head; //set iterator as value head
	for(i = 0; i < median_filter->num_nodes - 1; i++){
		if(value < it->value){
			if(i == 0){   //replace value head if new node is the smallest
				median_filter->value_head = new_node;
			}
			break;
		}
		it = it->next_value;
	}

	//insert new node in list
	it->prev_value->next_value = new_node;
	new_node->prev_value = it->prev_value;
	it->prev_value = new_node;
	new_node->next_value = it;

	//adjust median node
	if(i >= (median_filter->num_nodes / 2)) {
		median_filter->median_head = median_filter->median_head->next_value;
	}

	return median_get_f(median_filter);
}

float median_get_f( median_filter_f_t *median_filter ) {
	return median_filter->median_head->value;
}
