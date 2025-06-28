#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "interception.h"

// —— 宏定义：选择 G 和 H 共同触发的招式 ——
// 0: 八神庵 - 暗拂 (YamiBarai)
// 1: 陈国汉 - 铁球飞押しつぶし (TekkyuTobiOshitsubushi)
#define SKILL 0

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
void sendYamiBarai(InterceptionContext ctx, int device, bool leftSide)
{
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A; // 左站位用 D（→），右站位用 A（←）
    USHORT sc_punch = SC_I; // 重拳

    InterceptionKeyStroke stroke{};

    // ↓ down
    stroke.code = sc_down;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_DOWN);

    // →/← down (for ↘/↙)
    stroke.code = sc_forward;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_FORWARD);

    // ↓ up
    stroke.code = sc_down;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_DOWN);

    // →/← up
    stroke.code = sc_forward;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_FORWARD);

    // 重拳 down
    stroke.code = sc_punch;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_PUNCH);

    // 重拳 up
    stroke.code = sc_punch;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 陈国汉 - 铁球飞押しつぶし (↓↙←+C)
void sendTekkyuTobiOshitsubushi(InterceptionContext ctx, int device, bool leftSide)
{
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_A : SC_D; // 左站位用 A（←），右站位用 D（→）
    USHORT sc_punch = SC_I; // 重拳 (C)

    InterceptionKeyStroke stroke{};

    // ↓ down
    stroke.code = sc_down;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_DOWN);

    // ←/→ down (for ↙/↘)
    stroke.code = sc_forward;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_FORWARD);

    // ↓ up
    stroke.code = sc_down;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_DOWN);

    // ←/→ up
    stroke.code = sc_forward;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_FORWARD);

    // 重拳 down
    stroke.code = sc_punch;
    stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms(DELAY_PUNCH);

    // 重拳 up
    stroke.code = sc_punch;
    stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "TekkyuTobiOshitsubushi: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 程序入口
int main()
{
    // 1. 创建上下文
    InterceptionContext ctx = interception_create_context();
    if (!ctx) {
        std::cerr << "Failed to create Interception context\n";
        return -1;
    }

    // 2. 只处理键盘，并捕获所有按下/抬起事件
    interception_set_filter(ctx, interception_is_keyboard,
        INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);

    // #if DEBUG_LOG == 1
    std::cout << "YamiBarai injector running...\n";
    std::cout << "Press G for left-side (facing right), H for right-side (facing left). Ctrl+C to exit.\n";
    // #endif

    // 3. 主循环：读原始事件、处理 G/H、转发其它按键
    while (true) {
        int device = interception_wait(ctx);
        InterceptionStroke stroke_raw{};
        InterceptionKeyStroke& stroke = *(InterceptionKeyStroke*)&stroke_raw;

        if (interception_receive(ctx, device, &stroke_raw, 1) <= 0)
            continue;

        USHORT code = stroke.code;
        USHORT state = stroke.state;
        #if DEBUG_LOG == 1
        std::cout << "Received: code=" << code << ", state=" << state << std::endl;
        #endif

        // 拦截按下的 G 或 H
        if (state == INTERCEPTION_KEY_DOWN && code == SC_G) {
            // 左站位（面向右）
            #if SKILL == 0
                sendYamiBarai(ctx, device, true);
            #elif SKILL == 1
                sendTekkyuTobiOshitsubushi(ctx, device, true);
            #endif
            continue;
        }
        else if (state == INTERCEPTION_KEY_DOWN && code == SC_H) {
            // 右站位（面向左）
            #if SKILL == 0
                sendYamiBarai(ctx, device, false);
            #elif SKILL == 1
                sendTekkyuTobiOshitsubushi(ctx, device, false);
            #endif
            continue;
        }

        // 其余按键，原样转发
        interception_send(ctx, device, &stroke_raw, 1);
    }

    interception_destroy_context(ctx);
    return 0;
}