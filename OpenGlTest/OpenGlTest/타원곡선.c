////
////  타원곡선.c
////  OpenGlTest
////
////  Created by 심주흔 on 2024/04/08.
////
//
//#include <stdio.h>
//
//
//// 모듈로 p에서 제곱근을 계산하는 함수
//int mod_sqrt(int a, int p) {
//    for (int x = 0; x < p; x++) {
//        if ((x * x) % p == a % p) {
//            return x;
//        }
//    }
//    return -1; // 제곱근이 존재하지 않음
//}
//
//int main(){
//    int a, b, p, x, y;
//    printf("타원곡선의 파라미터 a, b와 유한 필드 p를 입력하세요: ");
//    scanf("%d %d %d", &a, &b, &p);
//    
//    printf("방정식 (x, y) 쌍:\n");
//    for (x = 0; x < p; x++) {
//        int y_squared = (x*x*x + a*x + b) % p;
//        y = mod_sqrt(y_squared, p);
//        if (y != -1) {
//            printf("(%d, %d)\n", x, y);
//            // 유한 필드 내에서 한 점에 대해 두 개의 y 값이 가능하다는 점을 고려해 추가 출력
//            if (y != 0) { // y = 0인 경우는 예외
//                printf("(%d, %d)\n", x, p - y);
//            }
//        }
//    }
//    
//    return 0;
//}
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//int mod_sqrt(int a, int p) {
//    for (int x = 0; x < p; x++) {
//        if ((x * x) % p == a % p) {
//            return x;
//        }
//    }
//    return -1; // 제곱근이 존재하지 않음
//}
//
//// 유한 필드 F_p에서의 모듈로 연산을 위한 함수
//int mod(int a, int p) {
//    int r = a % p;
//    return r < 0 ? r + p : r;
//}
//
//// 유한 필드 F_p에서의 역원을 계산하는 함수
//int mod_inverse(int a, int p) {
//    for (int x = 1; x < p; x++) {
//        if (mod(a * x, p) == 1) return x;
//    }
//    return -1; // 역원이 존재하지 않음
//}
//
//// 두 점 (x1, y1)과 (x2, y2)의 덧셈
//void point_addition(int x1, int y1, int x2, int y2, int a, int p, int* x3, int* y3) {
//    if (x1 == -1 && y1 == -1) {
//        *x3 = x2;
//        *y3 = y2;
//        return;
//    }
//    if (x2 == -1 && y2 == -1) {
//        *x3 = x1;
//        *y3 = y1;
//        return;
//    }
//
//    int s;
//    if (x1 == x2 && y1 == y2) { // P = Q
//        if (y1 == 0) { // 타원곡선의 무한원점
//            *x3 = *y3 = -1; // 무한원점을 결과로 설정
//            return;
//        }
//        s = mod((3 * x1 * x1 + a) * mod_inverse(2 * y1, p), p);
//    } else if (x1 == x2) {
//        *x3 = *y3 = -1; // 결과는 무한원점
//        return;
//    } else { // P != Q
//        s = mod((y2 - y1) * mod_inverse(x2 - x1, p), p);
//    }
//
//    *x3 = mod(s * s - x1 - x2, p);
//    *y3 = mod(s * (x1 - *x3) - y1, p);
//}
//
//int main() {
//    int a, b, p, x, y, x1, y1, x2, y2, x3, y3;
//    printf("타원곡선의 파라미터 a, b와 유한 필드 p를 입력하세요: ");
//    scanf("%d %d %d", &a, &b, &p);
//    
//    
//    printf("방정식 (x, y) 쌍:\n");
//        for (x = 0; x < p; x++) {
//            int y_squared = (x*x*x + a*x + b) % p;
//            y = mod_sqrt(y_squared, p);
//            if (y != -1) {
//                printf("(%d, %d)\n", x, y);
//                // 유한 필드 내에서 한 점에 대해 두 개의 y 값이 가능하다는 점을 고려해 추가 출력
//                if (y != 0) { // y = 0인 경우는 예외
//                    printf("(%d, %d)\n", x, p - y);
//                }
//            }
//        }
//
//    
//    
//    printf("덧셈할 첫 번째 점 (x1, y1)을 입력하세요: ");
//    scanf("%d %d", &x1, &y1);
//    printf("덧셈할 두 번째 점 (x2, y2)을 입력하세요: ");
//    scanf("%d %d", &x2, &y2);
//    
//    point_addition(x1, y1, x2, y2, a, p, &x3, &y3);
//    
//    if (x3 == -1 && y3 == -1)
//        printf("결과 점: O \n");
//    else
//        printf("결과 점: (%d, %d)\n", x3, y3);
//
//    return 0;
//}
