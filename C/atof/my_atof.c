#include "my_atof.h"

double my_atof(char *buf, ssize_t len) {
    double result_i = 0;
    double result_f = 0;
    int i = 0;
    double mult;
    double power = 10;
    if (len <= 0) {
        return result_i;
    }
    switch(buf[0]) {
        case MINUS:
            i = 1;
            break;
        default:
            i = 0;
            break;
    }
    
    int count = i;
    ssize_t dot = len;
    while (count < len) {
        if ('0' <= buf[count] && buf[count] <= '9' && len == dot) {
            if (count == 0) {
                result_i = buf[count] - TO_DIGIT;
            } else {
                result_i *= 10;
                result_i += (buf[count] - TO_DIGIT);
            }
        } else if('0' <= buf[len - (count - dot)] && buf[len - (count - dot)] <= '9' && len != dot) {
            result_f += (double)(buf[len - (count - dot)] - TO_DIGIT);
            result_f /= power;
        }
        else if (buf[count] == '.' && dot != len) {
            return 0;
        } else if (buf[count] == '.') {
            dot = count;
        } else {
            return 0;
        }
        count++;
    }

    if ((i && (result_i + result_f < 0)) || (!i && (result_f + result_i >= 0))) { //Integer Overflow
        return 0;
    }

    if (i) {
        return -(result_i + result_f);
    }

    return result_i + result_f;
}
