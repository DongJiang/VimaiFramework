#ifndef VL_API_H_
#define VL_API_H_

#ifdef __cplusplus
extern "C"
{ // extern "C"
#endif

#include <stdint.h>

    typedef struct
    {
        double position[3];  // xyz
        double rotation[4];  // quaternion in xyzw order
        int64_t area_id;

    } position_estimate_t;

    typedef struct
    {
        double position[3];
        double rotation[4];
    } ar_pose_t;

    typedef enum
    {
        VL_STATUS_OK,
        VL_STATUS_PENDING,
        VL_STATUS_ERR
    } VLStatus;

    VLStatus vl_features_from_pixels(int32_t *pixels, int32_t width, int32_t height, uint8_t *out_bytes,
                                     uint32_t max_bytes, uint32_t *out_num_bytes);
    VLStatus vl_features_from_image(const char *fname, uint8_t *out_bytes, uint32_t max_bytes, uint32_t *out_num_bytes);

    typedef void (*logger_t)(const char *);
    VLStatus vl_init_api(logger_t log_function);

    VLStatus vl_tracking_open_file(const char *fname, void **out_handle);
    VLStatus vl_tracking_open_bytes(const char *bytes, uint64_t numBytes, void **out_handle);

    VLStatus vl_tracking_destroy(void *handle);

    VLStatus vl_tracking_track_with_image(void *handle, int64_t time_millis, const char *image_filename,
                                          const ar_pose_t *in_ar_pose, const double *intrinsics);
    VLStatus vl_tracking_track_with_pixels(void *handle, int64_t time_millis, int32_t *pixels, int32_t width,
                                           int32_t height, ar_pose_t const *ar_pose, const double *intrinsics);

    VLStatus vl_tracking_track_with_features(void *handle, int64_t time_millis, const uint8_t *bytes, int32_t num_bytes,
                                             ar_pose_t const *ar_pose, const double *intrinsics);

    VLStatus vl_tracking_query(void *handle, int64_t current_time_millis, const ar_pose_t *in_ar_pose,
                               position_estimate_t *out_estimate);

    VLStatus vl_tracking_reset(void *handle);

    VLStatus vl_tracking_create(const char *fname, const char *const *imgs, uint32_t n_imgs, int k, int l);

#ifdef VL_ENABLE_DEVELOPMENT_API

    typedef struct
    {
        uint32_t num_dbow_results;
        uint32_t *dbow_indices;

    } vl_query_meta_t;
    VLStatus vl_tracking_get_query_meta(void *handle, vl_query_meta_t *meta);

    typedef struct
    {
        int64_t current_time_millis;
        char *image_filename;
        ar_pose_t ar_pose;
        position_estimate_t out_estimate;
        bool valid;
        const double *intrinsics;
    } time_step_t;
    VLStatus vl_tracking_query_batch(void *handle, time_step_t *steps, int32_t n_steps);

    typedef enum
    {
        DRAWCMD_SHAPE_CIRCLE,
    } DrawCommandShape;

    typedef struct
    {
        double x, y, z, rad;
        double r, g, b;
        const char *label;
        DrawCommandShape shape;
    } drawcommand_t;

    typedef void (*debug_draw_callback_ptr)(const drawcommand_t *);

    VLStatus vl_tracking_set_debug_draw_callback(debug_draw_callback_ptr ptr);

    VLStatus vl_tracking_set_hyperparams(void *handle, const double *params, uint32_t n_params);

    VLStatus vl_tracking_get_regressor(void *handle, const ar_pose_t *ar_pose, int64_t current_time_millis,
                                       double *out);

    VLStatus vl_tracking_get_top_k_minimum_distance(void *handle, const char *image_filename, int k, const double *pos,
                                                    const double *rot, double *out_score);

#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // VL_API_H_
