#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "interception.h"
#include <random>
#include <functional>
#include <vector>
#include <string>

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

// 随机延时函数，范围[min_ms, max_ms]
inline void ms_random(int min_ms, int max_ms) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_ms, max_ms);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
}

// 延时常量（适配拳皇97）
const int DELAY_DOWN = 40;    // 方向键按下
const int DELAY_FORWARD = 40; // 方向键组合
const int DELAY_BACKWARD = 40; // 方向键组合
const int DELAY_PUNCH = 30;   // 拳/脚

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
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1); 
    ms_random(DELAY_PUNCH - 10, DELAY_PUNCH + 10);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    #if DEBUG_LOG == 1
    std::cout << "YamiBarai: code=" << stroke.code << ", state=" << stroke.state << std::endl;
    #endif
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

// 八神庵 - 八稚女 (↓↘→↘↓↙←+A/C)
void sendYaotome(InterceptionContext ctx, int device, bool leftSide) {
    USHORT sc_down = SC_S;
    USHORT sc_forward = leftSide ? SC_D : SC_A;
    USHORT sc_backward = leftSide ? SC_A : SC_D;
    USHORT sc_punch = SC_I;

    InterceptionKeyStroke stroke{};

    // ↓
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);

    // ↘（下+前）
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);

    // 只松开下
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);

    // →（只保留前）
    // 这里其实前已经按下，无需重复

    // ↘（下+前）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);

    // ↓（只保留下）
    stroke.code = sc_forward; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);

    // ↙（下+后）
    stroke.code = sc_backward; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);

    // ←（只保留后）
    stroke.code = sc_down; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_DOWN - 10, DELAY_DOWN + 10);

    // 松开后
    stroke.code = sc_backward; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_FORWARD - 10, DELAY_FORWARD + 10);

    // 拳
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_DOWN;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
    ms_random(DELAY_PUNCH - 10, DELAY_PUNCH + 10);
    stroke.code = sc_punch; stroke.state = INTERCEPTION_KEY_UP;
    interception_send(ctx, device, (InterceptionStroke*)&stroke, 1);
}

struct SkillEntry {
    std::string name;
    std::function<void(InterceptionContext, int, bool)> func;
};

int main() {
    // 招式列表，后续只需在这里添加新招式
    std::vector<SkillEntry> skills = {
        { "Iori Yagami - YamiBarai (Dark Thrust)", sendYamiBarai },
        { "Iori Yagami - Yaotome (Maiden Masher)", sendYaotome }
        // 继续添加新招式，如 { "xxx", sendXxx }
    };

    std::cout << "YamiBarai - The King of Fighters '97 Move Injector\n";
    std::cout << "Select a move to trigger with G (left-side) or H (right-side):\n";
    for (size_t i = 0; i < skills.size(); ++i) {
        std::cout << i << ": " << skills[i].name << "\n";
    }
    std::cout << "Enter move number (0-" << (skills.size() - 1) << "): ";

    int skill = 0;
    std::cin >> skill;
    if (skill < 0 || skill >= static_cast<int>(skills.size())) {
        std::cerr << "Invalid choice, defaulting to " << skills[0].name << " (0)\n";
        skill = 0;
    }

    std::cout << "Selected move: " << skills[skill].name << "\n";
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
        if ((code == SC_G || code == SC_H) && state == INTERCEPTION_KEY_DOWN) {
            bool leftSide = (code == SC_G);
            skills[skill].func(ctx, device, leftSide);
            continue;
        }
        interception_send(ctx, device, &stroke_raw, 1);
    }
    interception_destroy_context(ctx);
    return 0;
}
