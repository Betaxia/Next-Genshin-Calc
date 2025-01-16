#include <iostream> 
#include <iomanip> // For setting output format 
#include <cstdio> 
#include <fstream> // For file input/output 
#include <locale> 
using namespace std; 

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
                cerr << "Invalid choice, please enter again." << endl;
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
                cerr << "Invalid choice, please enter again." << endl;
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
                cerr << "Invalid choice, please enter again." << endl;
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
            cerr << "Invalid choice, please enter again." << endl;
        }
    }

    makechoiceAimElement(choiceElement);
}

void calculateMaxDamage(double ecr_local = desiredCritRate, double step_local = step) {
    double a, cr, cd, ba, r, d = 0, ecr = ecr_local, em, s = step_local; 
    double aa = 0.0, acr = 0.0, acd = 0.0, aem = 0.0; 
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

	cout << fixed << setprecision(2); // Set output format to two decimal places 
    double pa, pcr, pcd, pd, pem = 0, ped, totpr; 
    makechoiceElement();
    if (choiceElement != 0){//not achieved
    	printLocalizedText("Enter elemental mastery:(test)", "请输入元素精通：（测试中）"); 
    	cin >> em;
    	double pr = (cr - 5) * 2 + cd - 50 + ((a - ba) / ba) / 0.0075 + em / 3; 
    	totpr = pr;
    	for (double i = 0.0; i <= pr; i += s) { 
        	pa = ba * (1 + i * 0.0075); 
        	for (double j = 0.0; j <= pr - i; j += s) {
        		pem = 3 * j;
        		for (double k = 0.0; (k <= pr - i - j) and (k <= ecr * 2 - 10); k += s){
        			pcr = 5 + k * 0.5; 
            		pcd = 50 + pr - i - j - k; 
            		pd = pa * (pcr * 0.01 * (1 + pcd * 0.01) + (1 - pcr * 0.01) * 1);
        	    	if (choiceElement == 1 and choiceAimElement == 1) ped = pd * 1.5 * (1 + (2.78 * em) / (em + 1400));
    	        	else if (choiceElement == 1 and choiceAimElement == 2) ped = pd * 2 * (1 + (2.78 * em) / (em + 1400));
	            	else if (choiceElement == 2 and choiceAimElement == 1) ped = pd * 2 * (1 + (2.78 * em) / (em + 1400));
            		else if (choiceElement == 3 and choiceAimElement == 1) ped = pd * 1.5 * (1 + (2.78 * em) / (em + 1400));
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
            	ped = pa * (pcr * 0.01 * (1 + pcd * 0.01) + (1 - pcr * 0.01));
        	    if(ped > d) {
    	        	d = ped; 
	            	acr = pcr; 
                	acd = pcd; 
                	aa = pa; 
				}
			}
			printLocalizedText("Program running:", "程序运行中：");
			cout << i / pr * 100 << "%" << endl;
    	} 
	}
    

    // Output results 
    printLocalizedText("Your character's maximum damage can reach:", "您的角色的最大伤害可以达到："); 
    cout << d * r * 0.01 << endl; 
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
            if (line.find("Step:") != string::npos) {
                size_t pos = line.find(':') + 1;
                desiredCritRate = stod(line.substr(pos));
            }
        }
        inFile.close();
    } else {
        cerr << "Unable to open file to load calculate step settings." << endl;
    }
}

int main() {
    // Load language setting from file (only once)
    loadLanguageSetting();

    // Load ECR setting from file (if exists)
    loadEcrValue();

	loadCalculateStep();
    // Print program title based on current language

    int choice;
    do {
    	printLocalizedText("Genshin Impact Max Damage Calculator v2.2.10.74c", "原神最大伤害计算器 v2.2.10.74c");
        printLocalizedText("1. Calculate maximum damage", "1. 计算最大伤害");
        printLocalizedText("2. Exit program", "2. 退出程序");
        printLocalizedText("3. Desired CRIT rate(if you used this program)", "3. 期望暴击率（如果你使用过此程序）");
        printLocalizedText("4. Change language", "4. 更改语言");
        printLocalizedText("5. Change calculate step(Calculation accuracy)", "5. 更改计算步长（计算精度）");
        printLocalizedText("Please enter your choice: ", "请输入您的选择：");
        cin >> choice;

        switch (choice) {
        case 1:
            calculateMaxDamage(desiredCritRate,step);
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
        case 5:
        	updateCalculateStep();
        	break;
        default:
            cerr << "Invalid choice, please enter again." << endl;
        }
    } while (choice != 2);

    return 0;
}
