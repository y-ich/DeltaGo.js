
#include <stdlib.h>
#include <math.h>

float static_buffer[4744537];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {4727209,3880489,1,48,19,19,19,19,5,5,1,1,1,1,2,2};
int meta_buf_1[] = {3880489,0,4642537,361,192,1200};
int meta_buf_2[] = {4642537,4642537,69312};
int meta_buf_3[] = {4642537,3880489,1,192,19,19,21,21,3,3,1,1,1,1,2,2};
int meta_buf_4[] = {3880489,230400,4642537,441,192,1728};
int meta_buf_5[] = {4642537,4642537,84672};
int meta_buf_6[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_7[] = {3880489,562176,4642537,441,192,1728};
int meta_buf_8[] = {4642537,4642537,84672};
int meta_buf_9[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_10[] = {3880489,893952,4642537,441,192,1728};
int meta_buf_11[] = {4642537,4642537,84672};
int meta_buf_12[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_13[] = {3880489,1225728,4642537,441,192,1728};
int meta_buf_14[] = {4642537,4642537,84672};
int meta_buf_15[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_16[] = {3880489,1557504,4642537,441,192,1728};
int meta_buf_17[] = {4642537,4642537,84672};
int meta_buf_18[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_19[] = {3880489,1889280,4642537,441,192,1728};
int meta_buf_20[] = {4642537,4642537,84672};
int meta_buf_21[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_22[] = {3880489,2221056,4642537,441,192,1728};
int meta_buf_23[] = {4642537,4642537,84672};
int meta_buf_24[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_25[] = {3880489,2552832,4642537,441,192,1728};
int meta_buf_26[] = {4642537,4642537,84672};
int meta_buf_27[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_28[] = {3880489,2884608,4642537,441,192,1728};
int meta_buf_29[] = {4642537,4642537,84672};
int meta_buf_30[] = {4642537,3880489,1,192,21,21,21,21,3,3,1,1,1,1,1,1};
int meta_buf_31[] = {3880489,3216384,4642537,441,192,1728};
int meta_buf_32[] = {4642537,4642537,84672};
int meta_buf_33[] = {4642537,3880489,1,192,21,21,19,19,3,3,1,1,1,1,0,0};
int meta_buf_34[] = {3880489,3548160,4504297,361,192,1728};
int meta_buf_35[] = {4504297,4504297,69312};
int meta_buf_36[] = {4504297,3879936,4573609,361,1,192};
int meta_buf_37[] = {3880128,4573609,4573609,361};
int meta_buf_38[] = {4573609,4573609,1,361};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38};

extern "C" void init() {
    //static_buffer = (float*)malloc(4744537 * sizeof(float));
}

extern "C" float* get_static_buffer(void) {
    return static_buffer;
}

extern "C" float* allocate_dynamic_buffer(int count) {
    if (dynamic_buffer) {
        free(dynamic_buffer);
        dynamic_buffer = nullptr;
    }
    dynamic_buffer = (float*)malloc(count * sizeof(float));
    return dynamic_buffer;
}

extern "C" float* get_dynamic_buffer(void) {
    return dynamic_buffer;
}
extern "C" void set_placeholder_value(int kernel_order, int offset, int value) {
    meta_buffers[kernel_order][offset] = value;
}

void im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(const int * meta_buffer)
{
    const float *im = (static_buffer + meta_buffer[0]);
    float *col = (static_buffer + meta_buffer[1]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[3];
    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int DH = meta_buffer[10];
    const int DW = meta_buffer[11];
    const int SH = meta_buffer[12];
    const int SW = meta_buffer[13];
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

    for (int gid = 0; gid < N*H2*W2*KH*KW*C1; gid += 1) {
        const int c1 = gid % C1;
        const int kw = gid / C1 % KW;
        const int kh = gid / C1 / KW % KH;
        const int w2 = gid / C1 / KW / KH % W2;
        const int h2 = gid / C1 / KW / KH / W2 % H2;
        const int  n = gid / C1 / KW / KH / W2 / H2;
        
        const int h1 = h2 * SH - PH + kh * DH;
        const int w1 = w2 * SW - PW + kw * DW;

        col[gid] = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n*H1+h1)*W1+w1)*C1+c1];
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(const int * meta_buffer)
{
    float *A = (static_buffer + meta_buffer[0]);
    float *B = (static_buffer + meta_buffer[1]);
    float *C = (static_buffer + meta_buffer[2]);

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, meta_buffer[3], meta_buffer[5]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, meta_buffer[5], meta_buffer[4]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, meta_buffer[3], meta_buffer[4]);

    c_mat.noalias() = a_mat * b_mat;
}


void relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    float * v2 = (static_buffer + meta_buffer[1]);
    const int D0 = meta_buffer[2];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v3 = v1[d0];
        float v4;
        {
            v4 = v3 > 0 ? v3 : 0;
        }
        v2[d0] = v4;
    }
}


void elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int D0 = meta_buffer[3];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v4 = v1[d0];
        const float v5 = v2[d0];
        float v6;
        {
            v6 = v5 + v4;
        }
        v3[d0] = v6;
    }
}


void softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int C = meta_buffer[3];

    for (int n = 0; n < N; n++) {
        float set_max = X[n * C];
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            if (val > set_max) {
                set_max = val;
            }
        }

        float sum_exp = 0.0F;
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            float exp_x = expf(val - set_max);
            sum_exp += exp_x;
            Y[n * C + c] = exp_x;
        }

        for (int c = 0; c < C; c++) {
            Y[n * C + c] /= sum_exp;
        }
    }
}

extern "C" void run() {
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_0);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_1);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_2);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_3);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_4);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_5);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_6);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_7);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_8);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_9);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_10);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_11);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_12);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_13);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_14);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_15);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_16);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_17);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_18);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_19);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_20);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_21);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_22);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_23);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_24);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_25);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_26);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_27);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_28);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_29);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_30);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_31);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_32);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_33);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_34);
relu_f2500ab135551f5089c6d7458938601c916475311dfd042f193c51fb(meta_buf_35);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_36);
elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(meta_buf_37);
softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(meta_buf_38);

}

