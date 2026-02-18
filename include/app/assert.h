
// Wrap any functions in app_init() or app_run() that return error_code_t
// To return the error to the main
#define ASSERT_OK(error_code)              \
    do                                     \
    {                                      \
        error_code_t err = error_code;     \
        if ((error_code_t)err != ERROR_OK) \
        {                                  \
            return err;                    \
        }                                  \
    } while (0)

#define ASSERT_TRUE(statement, error_code) \
    do                                     \
    {                                      \
        error_code_t err = error_code;     \
        if (!((bool)statement))            \
        {                                  \
            return err;                    \
        }                                  \
    } while (0)
