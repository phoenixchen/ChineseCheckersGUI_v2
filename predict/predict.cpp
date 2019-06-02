#include <stdio.h>

#include <vector>
#include "tf_utils.hpp"

#include "predict.h"

static void Deallocator(void* data, size_t length, void* arg) {
}

int predict(char *chess,Transform_1darray_2darray_Convert check){
    TF_Graph* graph = tf_utils::LoadGraph("assets/ChineseCheckers_model.pb");

    const int num_bytes_input1 = 9 * 9 * sizeof(float);
    const int num_bytes_input2 = 1 * sizeof(unsigned char);

    int64_t input_dims1[] = {9, 9};
    int64_t input_dims2[] = {1};

    float *values1 = new float[81];
    for(int i = 0; i < 81; i++) {
      values1[i] = 0.0000000f;
    }

    int row;
    int column;

    for(int i = 0; i < 256; i++) {

        check.transform_1darray_to_2darray(locatetransformrevers(i),&row,&column);
        switch(row-column){
            case -4:row = 0;break;
            case -3:row = 1;break;
            case -2:row = 2;break;
            case -1:row = 3;break;
            case  0:row = 4;break;
            case  1:row = 5;break;
            case  2:row = 6;break;
            case  3:row = 7;break;
            case  4:row = 8;break;
        }
        column = column -4;

        switch(chess[i]){
            case 1:
                values1[row*9+column] = -1.0000000f;
            break;
            case 2:
                values1[row*9+column] = 1.0000000f;
            break;
        }

    }
    unsigned char values2[] = {
    0,
    };

    std::vector<TF_Output> intput_name;
    intput_name.push_back({TF_GraphOperationByName(graph, "Placeholder"), 0});
    intput_name.push_back({TF_GraphOperationByName(graph, "is_training"), 0});

    std::vector<TF_Tensor*> input_tensor;
    input_tensor.push_back(TF_NewTensor(TF_FLOAT, input_dims1, 2, values1, num_bytes_input1, &Deallocator, 0));
    input_tensor.push_back(TF_NewTensor(TF_BOOL, input_dims2, 0, values2, num_bytes_input2, &Deallocator, 0));

    TF_Output output_name = {TF_GraphOperationByName(graph, "dense_2/Tanh"), 0};
    TF_Tensor* output_tensor = nullptr;


    TF_Status* status = TF_NewStatus();
    TF_SessionOptions* options = TF_NewSessionOptions();
    uint8_t config[7] ={0x32, 0x5, 0x20, 0x1, 0x2a, 0x1, 0x30};
    TF_SetConfig(options,(void*)config,7,status);
    TF_Session* sess = TF_NewSession(graph, options, status);
    TF_DeleteSessionOptions(options);

    TF_SessionRun(sess,
                nullptr, // Run options.
                &intput_name[0], &input_tensor[0], input_tensor.size(), // Input tensors name, input tensor values, number of inputs.
                &output_name, &output_tensor, 1, // Output tensors name, output tensor values, number of outputs.
                nullptr, 0, // Target operations, number of targets.
                nullptr, // Run metadata.
                status // Output status.
                );

    const auto output_data = static_cast<float*>(TF_TensorData(output_tensor));

    printf("\n%f\n",output_data[0]);

    int output_value = 100 - ((int)(((1 + output_data[0])/2)*100));

    tf_utils::DeleteGraph(graph);
    tf_utils::DeleteTensor(input_tensor[0]);
    tf_utils::DeleteTensor(input_tensor[1]);
    tf_utils::DeleteTensor(output_tensor);
    TF_DeleteStatus(status);
    return output_value;
}
