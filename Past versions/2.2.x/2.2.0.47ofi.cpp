#include <iostream> 
#include <iomanip> // For setting output format 
#include <cstdio> 
#include <fstream> // For file input/output 
#include <locale> 
#include <codecvt> 
using namespace std; 

// Global variable to store the current language 
string currentLanguage = "en"; 
double desiredCritRate = -1; // Default value, indicating not loaded from file

// Function to change language and update UI text 
void changeLanguage() { 
    string newLanguage; 
    cout << "Choose language: " << endl; 
    cout << "1. English" << endl; 
    cout << "2. 中文" << endl; 
    cout << "Enter your choice: "; 
    cin >> newLanguage; 

    if (newLanguage == "1") { 
        currentLanguage = "en"; 
    } else if (newLanguage == "2") { 
        currentLanguage = "zh"; 
    } else { 
        cout << "Invalid choice, language remains unchanged." << endl; 
        return; 
    } 

    // Save language choice to file 
    ofstream outFile("config_lang.ini"); 
    if (outFile.is_open()) { 
        outFile << "Language: " << currentLanguage << "\n"; 
        outFile.close(); 
    } else { 
        cerr << "Unable to open file to save language setting." << endl; 
    } 

    // Reload UI text based on new language (simplified example, normally use a map or resource file) 
    if (currentLanguage == "zh") { 
        cout << "语言已更改为中文。" << endl; 
    } else { 
        cout << "Language changed to English." << endl; 
    } 
} 

// Function to load language setting from file 
void loadLanguageSetting() { 
    ifstream inFile("config_lang.ini"); 
    string line; 

    if (inFile.is_open()) { 
        while (getline(inFile, line)) { 
            if (line.find("Language:") != string::npos) { 
                size_t pos = line.find(':') + 1; 
                currentLanguage = line.substr(pos); 
                if (!currentLanguage.empty() && currentLanguage[0] == ' ') {
    			currentLanguage = currentLanguage.substr(1); 
				}
                break; 
            } 
        } 
        inFile.close(); 
    } else { 
        cerr << "Unable to open file to load language setting." << endl; 
    } 

    // If no language setting found, default to English 
    if (currentLanguage.empty() || (currentLanguage != "en" && currentLanguage != "zh")) { 
        currentLanguage = "en"; 
    } 
} 

// Function to print localized text based on current language 
void printLocalizedText(const string& enText, const string& zhText) { 
    if (currentLanguage == "zh") { 
        cout << zhText << endl; 
    } else { 
        cout << enText << endl; 
    } 
} 

void calculateMaxDamage(double ecr = -1) {
    double a, cr, cd, ba, r, d = 0, ecr_local = ecr; 
    double aa = 0.0, acr = 0.0, acd = 0.0; 
    printLocalizedText("Enter your character's attack or health value:", "请输入您的角色的攻击或生命值："); 
    cin >> a; 
    printLocalizedText("Enter critical rate (%):", "请输入暴击率（%）："); 
    cin >> cr; 

    if (ecr_local == -1) { 
        printLocalizedText("Enter your desired maximum critical rate (%):", "请输入您期望的最大暴击率（%）："); 
        cin >> ecr_local; 
    } else { 
        printLocalizedText("Desired maximum critical rate you expected loaded from file:", "从文件中加载的你的期望最大暴击率（%）为："); 
        cout << ecr_local << endl; 
    } 

    printLocalizedText("Enter critical damage (%):", "请输入暴击伤害（%）："); 
    cin >> cd; 
    printLocalizedText("Enter base attack or health value:", "请输入基础攻击或生命值："); 
    cin >> ba; 
    printLocalizedText("Enter skill multiplier:", "请输入技能倍率："); 
    cin >> r; 

    double pr = (cr - 5) * 2 + cd - 50 + ((a - ba) / ba) / 0.0075; 
    double pa, pcr, pcd, pd; 
    for (double i = 0.1; i <= pr; i += 0.1) { 
        pa = ba * (1 + i * 0.0075); 
        for (double j = 0.1; (j <= ecr_local * 2 - 10) && (j <= pr - i); j += 0.1) { 
            pcr = 5 + j * 0.5; 
            pcd = 50 + pr - i - j; 
            pd = pa * pcr * 0.01 * (pcd + 100) * 0.01; 
            if (pd > d) { 
                d = pd; 
                acr = pcr; 
                acd = pcd; 
                aa = pa; 
            } 
        } 
    } 

    // Output results 
    cout << fixed << setprecision(2); // Set output format to two decimal places 
    printLocalizedText("Your character's maximum damage can reach:", "您的角色的最大伤害可以达到："); 
    cout << d * r * 0.01 << endl; 
    printLocalizedText("Your character's rating is: ", "您的角色的评分为："); 
    cout << pr << endl; 
    printLocalizedText("Character's attack or health value at this time:", "此时角色的攻击或生命值为："); 
    cout << aa << endl; 
    printLocalizedText("Character's critical rate is:", "角色的暴击率为："); 
    cout << acr << "%" << endl; 
    printLocalizedText("Character's critical damage is:", "角色的暴击伤害为："); 
    cout << acd << "%" << endl; 

    // Save ecr_local to file 
    ofstream outFile("config_ecd.ini"); // Changed filename to config_ecd.ini
    if (outFile.is_open()) { 
        outFile << "Desired CRIT rate: " << ecr_local << ".\n"; 
        outFile.close(); 
    } else { 
        cerr << "Unable to open file to save ecr." << endl; 
    } 

    // Also update the global variable for desired critical rate
    desiredCritRate = ecr_local;
} 

void updateEcrValue() { 
    double newEcr; 
    printLocalizedText("Enter the new desired maximum critical rate (%):", "请输入新的期望最大暴击率（%）："); 
    cin >> newEcr; 

    // Update the global variable
    desiredCritRate = newEcr;

    ofstream outFileDesiredCRITrate("config_ecd.ini"); // Changed filename to config_ecd.ini
    if (outFileDesiredCRITrate.is_open()) { 
        outFileDesiredCRITrate << "Desired CRIT rate: " << newEcr << ".\n"; 
        outFileDesiredCRITrate.close(); 
        printLocalizedText("Desired CRIT rate value updated successfully!", "期望最大暴击率值已成功更新！"); 
        printLocalizedText("Please restart this program", "请重新启动此程序"); 
    } else { 
        cerr << "Unable to open file to update desired CRIT rate." << endl; 
    } 
} 

int main() { 
    // Load language setting from file 
    loadLanguageSetting(); 

    // Load ECR setting from file (if exists)
    ifstream inFile("config_ecd.ini"); // Changed filename to config_ecd.ini
    string line; 
    if (inFile.is_open()) { 
        while (getline(inFile, line)) { 
            if (line.find("Desired CRIT rate:") != string::npos) { 
                size_t pos = line.find(':') + 1; 
                desiredCritRate = stod(line.substr(pos)); 
            } 
        } 
        inFile.close();
    } else {
        cerr << "Unable to open file to load settings." << endl;
    }
 
    // Load localized UI text
    loadLanguageSetting();
 
    // Print program title based on current language
    printLocalizedText("Genshin Impact Max Damage Calculator v2.2.0.47ofi-en", "原神最大伤害计算器 v2.2.0.47ofi-zh");
 
    int choice;
    do {
        printLocalizedText("1. Calculate maximum damage", "1. 计算最大伤害");
        printLocalizedText("2. Exit program", "2. 退出程序");
        printLocalizedText("3. Desired CRIT rate(if you used this program)", "3. 期望暴击率（如果你使用过此程序）");
        printLocalizedText("4. Change language", "4. 更改语言");
        printLocalizedText("Please enter your choice: ", "请输入您的选择：");
        cin >> choice;
 
        switch (choice) {
            case 1:
                calculateMaxDamage(desiredCritRate);
                break;
            case 2:
                printLocalizedText("Thank you for using, goodbye!", "感谢使用，再见！");
                break;
            case 3:
                updateEcrValue(); // Call the function to update ECR
                break;
            case 4:
                changeLanguage(); // Call the function to change language
                break;
            default:
                printLocalizedText("Invalid choice, please enter again.", "无效选择，请重新输入。");
        }
    } while (choice != 2);
 
    return 0;
}
