//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//// 모듈로 p에서 제곱근을 계산하는 함수
//// 이 함수는 특정 값 a에 대해 x^2 ≡ a (mod p)를 만족하는 x를 찾습니다.
//int mod_sqrt(int a, int p) {
//    for (int x = 0; x < p; x++) {
//        if ((x * x) % p == a % p) {
//            return x; // 제곱근 x 반환
//        }
//    }
//    return -1; // 해당하는 제곱근이 없을 경우 -1 반환
//}
//
//// 유한 필드 F_p에서의 모듈로 연산을 보정하는 함수
//// 음수가 나오지 않도록 보장합니다.
//int mod(int a, int p) {
//    int r = a % p;
//    return r < 0 ? r + p : r;
//}
//
//// 유한 필드 F_p에서의 역원을 계산하는 함수
//// a의 모듈로 p에 대한 역원은 a * x ≡ 1 (mod p)를 만족하는 x입니다.
//int mod_inverse(int a, int p) {
//    for (int x = 1; x < p; x++) {
//        if (mod(a * x, p) == 1) return x; // 역원 x 반환
//    }
//    return -1; // 역원이 존재하지 않을 경우 -1 반환
//}
//
//// 두 점 (x1, y1)과 (x2, y2)의 덧셈을 수행하는 함수
//// 타원곡선 상의 두 점을 더해 새로운 점 (x3, y3)를 계산합니다.
//void point_addition(int x1, int y1, int x2, int y2, int a, int p, int* x3, int* y3) {
//    // 두 점 중 하나가 무한원점인 경우, 다른 점을 반환합니다.
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
//    // 두 점이 같은 경우와 다른 경우에 대해 기울기 s를 계산합니다.
//    if (x1 == x2 && y1 == y2) {
//        // P = Q의 경우, 점 P에서의 접선의 기울기를 계산합니다.
//        if (y1 == 0) {
//            *x3 = *y3 = -1; // 타원곡선의 무한원점을 결과로 설정
//            return;
//        }
//        s = mod((3 * x1 * x1 + a) * mod_inverse(2 * y1, p), p);
//    } else if (x1 == x2) {
//        *x3 = *y3 = -1; // 두 점이 수직으로 만나면 결과는 무한원점
//        return;
//    } else {
//        // P ≠ Q의 경우, 두 점을 지나는 직선의 기울기를 계산합니다.
//        s = mod((y2 - y1) * mod_inverse(x2 - x1, p), p);
//    }
//
//    // 새로운 점 (x3, y3)를 계산합니다.
//    *x3 = mod(s * s - x1 - x2, p);
//    *y3 = mod(s * (x1 - *x3) - y1, p);
//}
//
//int main() {
//    int a, b, p, x, y, x1, y1, x2, y2, x3, y3;
//    printf("타원곡선의 파라미터 a, b와 유한 필드 p를 입력하세요: ");
//    scanf("%d %d %d", &a, &b, &p);
//    
//    // 타원곡선 상의 점들을 찾아 출력합니다.
//    printf("타원곡선 상의 (x, y) 쌍:\n");
//    for (x = 0; x < p; x++) {
//        int y_squared = (x*x*x + a*x + b) % p;
//        y = mod_sqrt(y_squared, p);
//        if (y != -1) {
//            printf("(%d, %d)\n", x, y);
//            // 유한 필드 내에서 한 점에 대해 두 개의 y 값이 가능합니다.
//            if (y != 0) {
//                printf("(%d, %d)\n", x, p - y);
//            }
//        }
//    }
//    
//    // 사용자로부터 덧셈을 수행할 두 점을 입력받습니다.
//    printf("덧셈할 첫 번째 점 (x1, y1)을 입력하세요: ");
//    scanf("%d %d", &x1, &y1);
//    printf("덧셈할 두 번째 점 (x2, y2)을 입력하세요: ");
//    scanf("%d %d", &x2, &y2);
//    
//    // 입력받은 두 점의 덧셈을 수행합니다.
//    point_addition(x1, y1, x2, y2, a, p, &x3, &y3);
//    
//    // 덧셈 결과를 출력합니다.
//    if (x3 == -1 && y3 == -1)
//        printf("결과 점: O (무한원점)\n");
//    else
//        printf("결과 점: (%d, %d)\n", x3, y3);
//
//    return 0;
//}
//
