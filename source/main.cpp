/*******************************************************************************
 * @author    xkuuo (ke.l@foxmail.com)
 * @date      2026-06-21
 * @return    int
 *
 * @brief     程序入口
 *
 ******************************************************************************/

#include <conio.h>
#include <iostream>
#include <opencv2/highgui.hpp>

using cv::destroyAllWindows;
using std::cin;
using std::cout;
using std::endl;

extern int exp1_main(void);
extern int exp2_main(void);
extern int exp3_main(void);
extern int exp4_main(void);
extern int exp5_main(void);
extern int exp6_main(void);

void cleanupAllWindows()
{
    destroyAllWindows();
    cout << "\n已关闭窗口，按任意键继续..." << endl;
    while(!_kbhit())
        ;
}

int main(void)
{
    int choice = -1;

    while(choice != 0)
    {
        cout << "\n========================================" << endl;
        cout << "    数字图像处理实验选择菜单" << endl;
        cout << "========================================" << endl;
        cout << "  1. 灰度直方图与图像增强 (摄像头)" << endl;
        cout << "  2. 双边滤波" << endl;
        cout << "  3. 纹理特征提取" << endl;
        cout << "  4. 色彩鲜艳度调整" << endl;
        cout << "  5. 模板匹配" << endl;
        cout << "  6. K-Means 图像分割" << endl;
        cout << "  0. 退出" << endl;
        cout << "========================================" << endl;
        cout << "请选择实验编号: ";

        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "无效输入，请重新选择！" << endl;
            continue;
        }

        switch(choice)
        {
            case 1 :
                exp1_main();
                cleanupAllWindows();
                break;
            case 2 :
                exp2_main();
                cleanupAllWindows();
                break;
            case 3 :
                exp3_main();
                cleanupAllWindows();
                break;
            case 4 :
                exp4_main();
                cleanupAllWindows();
                break;
            case 5 :
                exp5_main();
                cleanupAllWindows();
                break;
            case 6 :
                exp6_main();
                cleanupAllWindows();
                break;
            case 0  : cout << "退出程序，再见！" << endl; break;
            default : cout << "无效选项，请重新选择！" << endl; break;
        }
    }
    return 0;
}
