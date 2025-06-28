#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "interception.h"

// —— 宏定义：控制是否打印调试日志 ——
// 1: 启用调试日志, 0: 禁用调试日志
#define DEBUG_LOG 0

// —— 扫描码定义（基于 US 键盘） ——
constexpr USHORT SC_W = 0x11; // 上
constexpr USHORT SC_S = 0x1F; // 下
constexpr USHORT SC_A = 0x1E; // 左
constexpr USHORT SC_D = 0x20; // 右
constexpr USHORT SC_U = 0x16; // 轻拳 (A)
constexpr USHORT SC_J = 0x24; // 轻脚 (B)
constexpr USHORT SC_I = 0x17; // 重拳 (C)
constexpr USHORT SC_K = 0x25; // 重脚 (D)
constexpr USHORT SC_G = 0x22; // 左站位触发
constexpr USHORT SC_H = 0x23; // 右站位触发

// 延时单位
inline void ms(int t) { std::this_thread::sleep_for(std::chrono::milliseconds(t)); }

// 延时常量（适配拳皇97）
const int DELAY_DOWN = 25;    // 方向键按下
const int DELAY_FORWARD = 25; // 方向键组合
const int DELAY_PUNCH = 15;   // 拳/脚

// 八神庵 - 暗拂 (↓↘→+C)
void sendYamiBarai(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_punch = SC_I;
    InterceptionKeyStroke stroke{};
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 陈国汉 - 铁球飞押しつぶし (↓↙←+C)
void sendTekkyuTobiOshitsubushi(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_A : SC_D;
    USHORT sc_punch = SC_I;
    InterceptionKeyStroke stroke{};
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 八神庵 - 鬼烧 (↓↘→+A)
void sendOniyaki(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_punch = SC_U;
    InterceptionKeyStroke stroke{};
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "Oniyaki: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 大门五郎 - 地雷震 (↓↘→↓↘→+A)
void sendJiraiShin(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_punch = SC_U;
    InterceptionKeyStroke stroke{};
    // 第一组 ↓↘→
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    // 第二组 ↓↘→
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_DOWN);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_FORWARD);
    // 拳
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); ms(DELAY_PUNCH);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "JiraiShin: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

int main() {
    // 提示用户选择招式
    std::cout << "YamiBarai - The King of Fighters '97 Move Injector\n";
    std::cout << "Select a move to trigger with G (left-side) or H (right-side):\n";
    std::cout << "0: Iori Yagami - YamiBarai (Dark Thrust)\n";
    std::cout << "1: Chang Koehan - Tekkyu Tobi Oshitsubushi (Iron Ball Flying Crush)\n";
    std::cout << "2: Iori Yagami - Oniyaki (Demon Scorcher)\n";
    std::cout << "3: Goro Daimon - Jirai Shin (Earthquake)\n";
    std::cout << "Enter move number (0-3): ";
    
    int skill;
    std::cin >> skill;
    if (skill < 0 || skill > 3) {
        std::cerr << "Invalid choice, defaulting to YamiBarai (0)\n";
        skill = 0;
    }
    
    // 显示选择结果
    std::cout << "Selected move: ";
    switch (skill) {
        case 0: std::cout << "YamiBarai\n"; break;
        case 1: std::cout << "Tekkyu Tobi Oshitsubushi\n"; break;
        case 2: std::cout << "Oniyaki\n"; break;
        case 3: std::cout << "Jirai Shin\n"; break;
    }
    std::cout << "Press G for left-side (facing right), H for right-side (facing left). Ctrl+C to exit.\n";

    InterceptionContext ctx = interception_create_context();
    if (!ctx) {
        std::cerr << "Failed to create Interception context\n";
        return -1;
    }
    interception_set_filter(ctx, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai injector running...\n";
    #endif
    while (true) {
        int device = interception_wait(ctx);
        InterceptionStroke stroke_raw{};
        InterceptionKeyStroke& stroke = *(InterceptionKeyStroke*)&stroke_raw;
        if (interception_receive(ctx, device, &stroke_raw, 1) <= 0) continue;
        USHORT code = stroke.code;
        USHORT state = stroke.state;
        #if DEBUG_LOG == 1
        std::cout << "Received: code=" << code << ", state=" << state << std::endl;
        #endif
        if (state == INTERCEPTION_KEY_DOWN && code == SC_G) {
            switch (skill) {
                case 0: sendYamiBarai(ctx, device, true); break;
                case 1: sendTekkyuTobiOshitsubushi(ctx, device, true); break;
                case 2: sendOniyaki(ctx, device, true); break;
                case 3: sendJiraiShin(ctx, device, true); break;
            }
            continue;
        }
        else if (state == INTERCEPTION_KEY_DOWN && code == SC_H) {
            switch (skill) {
                case 0: sendYamiBarai(ctx, device, false); break;
                case 1: sendTekkyuTobiOshitsubushi(ctx, device, false); break;
                case 2: sendOniyaki(ctx, device, false); break;
                case 3: sendJiraiShin(ctx, device, false); break;
            }
            continue;
        }
        interception_send(ctx, device, &stroke_raw, 1);
    }
    interception_destroy_context(ctx);
    return 0;
}
