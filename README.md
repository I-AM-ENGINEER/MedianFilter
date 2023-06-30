# Median Filter
This is an CPU efficient implementation of median filter, implement uint 8/16/32, int 8/16/32 and float types. No dynamic memory usage.
Useful for spike and noise removal from analog signals or other DSP
Also known as "salt-and-pepper noise" or "impulse noise" filter

# Example code
This is a pseudo-code showing how one can use this library
```c
#define FILTER_NODES_COUNT 11 // WARNING!!! ONLY ODD VALUES!
median_filter_u16_t filter;
median_node_u16_t nodes[FILTER_NODES_COUNT];

uint16_t ADC_value;
uint16_t ADC_value_filtered;

int main(void){
    // initialize filter with zeros values as default (0.0f)
    median_init_u16(&filter, nodes, FILTER_NODES_COUNT, 0.0f);

    while(1){
        ADC_value = ADC_Get_Value();
        median_insert_u16(&filter, h);
        ADC_value_filtered = median_get_u16(&filter);
        printf("%hu", ADC_value_filtered);
    }

    return 0;
}
```

Function ```median_insert_X()``` insert new value and return filtered, while function ```median_get_X()``` only return filtred value without update filter.

For signed values use ``` i8 / i16 / i32 ```, for unsigned ``` u8 / u16 / u32 ```, for float ``` f ```

# Acknowledgement
I fork and modify this library: https://github.com/accabog/MedianFilter
