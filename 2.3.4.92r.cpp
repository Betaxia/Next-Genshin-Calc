#include <iostream> 
#include <iomanip> // For setting output format 
#include <fstream> // For file input/output 
#include <cstdlib>
using namespace std; 
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)

// Global variable to store the current language 
string currentLanguage = "en"; 
double desiredCritRate = 100; // Default value, indicating not loaded from file
double step = 0.1;
int choiceAimElement;
int choiceElement;

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
    system("cls");

    // Save language choice to file 
    ofstream outFile("config_lang.ini"); 
    if (outFile.is_open()) { 
        outFile << "Language:" << currentLanguage << "\n"; 
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
                break; 
        	} 
    	} 
        inFile.close();
	}
    else { 
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

void makechoiceAimElement(int choiceElement) {
    bool valid = false;

    if (choiceElement == 0) {
        return;
    } 
	else if (choiceElement == 1) {
        printLocalizedText("Choose the element of your aim attached", "选择你的攻击目标的元素附着");
        printLocalizedText("1.Hydro", "1.水");
        printLocalizedText("2.Cyro", "2.冰");
        while (!valid) {
            cin >> choiceAimElement;
            if (choiceAimElement == 1 || choiceAimElement == 2) {
                valid = true;
            } else {
                printLocalizedText("Invalid choice, please enter again.", "无效选择，请重新输入。");
            }
        }
    } 
	else if (choiceElement == 2) { 
        printLocalizedText("1.Pyro", "1.火");
        while (!valid) {
            cin >> choiceAimElement;
            if (choiceAimElement == 1) {
                valid = true;
            } else {
                printLocalizedText("Invalid choice, please enter again.", "无效选择，请重新输入。");
            }
        }
    }
    else if (choiceElement == 3) { 
        printLocalizedText("1.Pyro", "1.火");
        while (!valid) {
            cin >> choiceAimElement;
            if (choiceAimElement == 1) {
                valid = true;
            } else {
                printLocalizedText("Invalid choice, please enter again.", "无效选择，请重新输入。");
            }
        }
	}
}

void makechoiceElement() {
    bool valid = false;

    while (!valid) {
    	printLocalizedText("Calculate for element mastery(It may take a long time)", "计算元素精通部分（可能花费较长时间）");
        printLocalizedText("Choose the element of your character", "选择你的角色的元素");
		printLocalizedText("1.Pyro", "1.火");
		printLocalizedText("2.Hydro", "2.水");
		printLocalizedText("3.Cryo", "3.冰");
		printLocalizedText("0.Skip", "0.跳过");
        cin >> choiceElement;

        if (choiceElement >= 0 && choiceElement <= 3) {
            valid = true;
        } else {
            printLocalizedText("Invalid choice, please enter again.", "无效选择，请重新输入。");
        }
    }

    makechoiceAimElement(choiceElement);
}

void calculateMaxDamage(double ecr_local = desiredCritRate, double step_local = step) {
    double a, cr, cd, ba, r, m = 0, d = 0, ecr = ecr_local, em, s = step_local; 
    double aa = 0.0, acr = 0.0, acd = 0.0, aem = 0.0; /*am = 0.0*/ 
    printLocalizedText("Enter your character's attack or health value:", "请输入您的角色的攻击或生命值："); 
    cin >> a; 
    printLocalizedText("Enter critical rate (%):", "请输入暴击率（%）："); 
    cin >> cr; 
    printLocalizedText("Desired maximum critical rate you expected loaded from file(default value:100%):", "从文件中(默认值:100%)加载的你的期望最大暴击率（%）为："); 
    cout << ecr << endl; 
    printLocalizedText("Enter critical damage (%):", "请输入暴击伤害（%）："); 
    cin >> cd; 
    printLocalizedText("Enter base attack or health value:", "请输入基础攻击或生命值："); 
    cin >> ba; 
    printLocalizedText("Enter skill multiplier:", "请输入技能倍率："); 
    cin >> r;
	printLocalizedText("Enter Elemental damage bonus:", "请输入元素伤害加成："); 
    cin >> m; 

	cout << fixed << setprecision(2); // Set output format to two decimal places 
    double pa, pcr, pcd, pd, pem = 0, ped, totpr; 
    makechoiceElement();
    if (choiceElement != 0){
    	printLocalizedText("Enter elemental mastery", "请输入元素精通："); 
    	cin >> em;
    	double pr = (cr - 5) * 2 + cd - 50 + ((a - ba) / ba) / 0.0075 + em / 3; 
    	totpr = pr;
    	for (double i = 0.0; i <= pr; i += s) { 
        	pa = ba * (1 + i * 0.0075); 
        	for (double j = 0.0; j <= pr - i; j += s) {
        		pem = 3 * j;
        		for (double k = 0.0; (k <= pr - i - j) and (k <= ecr * 2 - 10); k += s) {
        			pcr = 5 + k * 0.5; 
            		pcd = 50 + pr - i - j - k; 
            		pd = pa * (pcr * 0.01 * (1 + pcd * 0.01) + (1 - pcr * 0.01) * 1);
        	    	if (choiceElement == 1 and choiceAimElement == 1) ped = pd * 1.5 * (1 + (2.78 * pem) / (pem + 1400));
    	        	else if (choiceElement == 1 and choiceAimElement == 2) ped = pd * 2 * (1 + (2.78 * pem) / (pem + 1400));
	            	else if (choiceElement == 2 and choiceAimElement == 1) ped = pd * 2 * (1 + (2.78 * pem) / (pem + 1400));
            		else if (choiceElement == 3 and choiceAimElement == 1) ped = pd * 1.5 * (1 + (2.78 * pem) / (pem + 1400));
        	    	if(ped > d) {
    	        		d = ped; 
	            		acr = pcr; 
                		acd = pcd; 
                		aa = pa; 
            	    	aem = pem;
					}
				}
			}
			printLocalizedText("Program running:", "程序运行中：");
			cout << i / pr * 100 << "%" << endl;
    	} 
	}
	else {
		double pr = (cr - 5) * 2 + cd - 50 + ((a - ba) / ba) / 0.0075; 
		totpr = pr;
		for (double i = 0.0; i <= pr; i += s) { 
        	pa = ba * (1 + i * 0.0075); 
        	for (double j = 0.0; (j <= pr - i) and (j <= ecr * 2 - 10); j += s) {
        		pcr = 5 + j * 0.5;
            	pcd = 50 + pr - i - j; 
            	ped = pa * (pcr * 0.01 * (1 + pcd * 0.01) + (1 - pcr * 0.01) * 1);
        	    if(ped > d) {
    	        	d = ped; 
	            	acr = pcr; 
                	acd = pcd; 
                	aa = pa; 
            		aem = pem;
				}
			}
			printLocalizedText("Program running:", "程序运行中：");
			cout << i / pr * 100 << "%" << endl;
    	} 
	}
    system("cls");

    // Output results 
    printLocalizedText("Your character's maximum damage can reach:", "您的角色的最大伤害可以达到："); 
    cout << d * r * 0.01 * (m + 100) * 0.01 << endl; 
    printLocalizedText("Your character's rating is: ", "您的角色的评分为："); 
    cout << totpr << endl; 
    printLocalizedText("Character's attack or health value at this time:", "此时角色的攻击或生命值为："); 
    cout << aa << endl; 
    printLocalizedText("Character's critical rate is:", "角色的暴击率为："); 
    cout << acr << "%" << endl; 
    printLocalizedText("Character's critical damage is:", "角色的暴击伤害为："); 
    cout << acd << "%" << endl; 
    if (choiceElement != 0){
    	printLocalizedText("Character's elemental mastery is:", "角色的元素精通为：");
		cout << aem << endl;
	}
} 

void updateEcrValue() { 
    double newEcr; 
    printLocalizedText("Enter the new desired maximum critical rate (%):", "请输入新的期望最大暴击率（%）："); 
    cin >> newEcr; 

    // Update the global variable
    desiredCritRate = newEcr;
    system("cls");

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

void loadEcrValue() {
	ifstream inFile("config_ecd.ini");
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
        cerr << "Unable to open file to load desired CRIT rate." << endl;
    }
}

void updateCalculateStep() { 
    double newStep; 
    printLocalizedText("Enter the new step:", "请输入新的计算步长："); 
    printLocalizedText("Tip:the shorter step is,the more time cost", "提示：步长越短，花费时间越长"); 
    printLocalizedText("Recommended value:0.1", "建议值：0.1"); 
    cin >> newStep; 

    // Update the global variable
    step = newStep;

    ofstream outFileStep("config_Step.ini"); // Changed filename to config_ecd.ini
    if (outFileStep.is_open()) { 
        outFileStep << "Step: " << newStep << ".\n"; 
        outFileStep.close(); 
        printLocalizedText("Step value updated successfully!", "计算步长已成功更新！"); 
        printLocalizedText("Please restart this program", "请重新启动此程序"); 
    } else { 
        cerr << "Unable to open file to update calculate step." << endl; 
    } 
} 

void loadCalculateStep() {
	ifstream inFile("config_Step.ini");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find("Calculate step:") != string::npos) {
                size_t pos = line.find(':') + 1;
                step = stod(line.substr(pos));
            }
        }
        inFile.close();
    } else {
        cerr << "Unable to open file to load calculate step settings." << endl;
    }
    system("cls");
}

int main() {
	ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    // Load language setting from file (only once)
    loadLanguageSetting();

    // Load ECR setting from file (if exists)
    loadEcrValue();

	loadCalculateStep();
    // Print program title based on current language

    int choice;
    do {
    	printLocalizedText("Genshin Impact Max Damage Calculator v2.3.4.92r", "原神最大伤害计算器 v2.3.1.80r");
        printLocalizedText("1. Calculate maximum damage", "1. 计算最大伤害");
        printLocalizedText("2. Exit program", "2. 退出程序");
        printLocalizedText("3. Desired CRIT rate(if you used this program)", "3. 期望暴击率（如果你使用过此程序）");
        printLocalizedText("4. Change language", "4. 更改语言");
        printLocalizedText("5. Change calculate step(Calculation accuracy)", "5. 更改计算步长（计算精度）");
        printLocalizedText("Please enter your choice: ", "请输入您的选择：");
        cin >> choice;

        switch (choice) {
        case 1:
        	system("cls");
            calculateMaxDamage(desiredCritRate);
            break;
        case 2:
            printLocalizedText("Thank you for using, goodbye!", "感谢使用，再见！");
            break;
        case 3:
        	system("cls");
            updateEcrValue(); // Call the function to update ECR
            break;
        case 4:
        	system("cls");
            changeLanguage(); // Call the function to change language
            break;
        case 5:
        	system("cls");
        	updateCalculateStep();
        	break;
        default:
            cerr << "Invalid choice, please enter again." << endl;
        }
    } while (choice != 2);

    return 0;
}