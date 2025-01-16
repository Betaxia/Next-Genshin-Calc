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
    cout << "2. ����" << endl; 
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
        cout << "�����Ѹ���Ϊ���ġ�" << endl; 
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
        printLocalizedText("Choose the element of your aim attached", "ѡ����Ĺ���Ŀ���Ԫ�ظ���");
        printLocalizedText("1.Hydro", "1.ˮ");
        printLocalizedText("2.Cyro", "2.��");
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
        printLocalizedText("1.Pyro", "1.��");
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
        printLocalizedText("1.Pyro", "1.��");
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
    	printLocalizedText("Calculate for element mastery(It may take a long time)", "����Ԫ�ؾ�ͨ���֣����ܻ��ѽϳ�ʱ�䣩");
        printLocalizedText("Choose the element of your character", "ѡ����Ľ�ɫ��Ԫ��");
		printLocalizedText("1.Pyro", "1.��");
		printLocalizedText("2.Hydro", "2.ˮ");
		printLocalizedText("3.Cryo", "3.��");
		printLocalizedText("0.Skip", "0.����");
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
    printLocalizedText("Enter your character's attack or health value:", "���������Ľ�ɫ�Ĺ���������ֵ��"); 
    cin >> a; 
    printLocalizedText("Enter critical rate (%):", "�����뱩���ʣ�%����"); 
    cin >> cr; 
    printLocalizedText("Desired maximum critical rate you expected loaded from file(default value:100%):", "���ļ���(Ĭ��ֵ:100%)���ص����������󱩻��ʣ�%��Ϊ��"); 
    cout << ecr << endl; 
    printLocalizedText("Enter critical damage (%):", "�����뱩���˺���%����"); 
    cin >> cd; 
    printLocalizedText("Enter base attack or health value:", "�������������������ֵ��"); 
    cin >> ba; 
    printLocalizedText("Enter skill multiplier:", "�����뼼�ܱ��ʣ�"); 
    cin >> r; 

	cout << fixed << setprecision(2); // Set output format to two decimal places 
    double pa, pcr, pcd, pd, pem = 0, ped, totpr; 
    makechoiceElement();
    if (choiceElement != 0){//not achieved
    	printLocalizedText("Enter elemental mastery:(test)", "������Ԫ�ؾ�ͨ���������У�"); 
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
			printLocalizedText("Program running:", "���������У�");
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
			printLocalizedText("Program running:", "���������У�");
			cout << i / pr * 100 << "%" << endl;
    	} 
	}
    

    // Output results 
    printLocalizedText("Your character's maximum damage can reach:", "���Ľ�ɫ������˺����Դﵽ��"); 
    cout << d * r * 0.01 << endl; 
    printLocalizedText("Your character's rating is: ", "���Ľ�ɫ������Ϊ��"); 
    cout << totpr << endl; 
    printLocalizedText("Character's attack or health value at this time:", "��ʱ��ɫ�Ĺ���������ֵΪ��"); 
    cout << aa << endl; 
    printLocalizedText("Character's critical rate is:", "��ɫ�ı�����Ϊ��"); 
    cout << acr << "%" << endl; 
    printLocalizedText("Character's critical damage is:", "��ɫ�ı����˺�Ϊ��"); 
    cout << acd << "%" << endl; 
    if (choiceElement != 0){
    	printLocalizedText("Character's elemental mastery is:", "��ɫ��Ԫ�ؾ�ͨΪ��");
		cout << aem << endl;
	}
} 

void updateEcrValue() { 
    double newEcr; 
    printLocalizedText("Enter the new desired maximum critical rate (%):", "�������µ�������󱩻��ʣ�%����"); 
    cin >> newEcr; 

    // Update the global variable
    desiredCritRate = newEcr;

    ofstream outFileDesiredCRITrate("config_ecd.ini"); // Changed filename to config_ecd.ini
    if (outFileDesiredCRITrate.is_open()) { 
        outFileDesiredCRITrate << "Desired CRIT rate: " << newEcr << ".\n"; 
        outFileDesiredCRITrate.close(); 
        printLocalizedText("Desired CRIT rate value updated successfully!", "������󱩻���ֵ�ѳɹ����£�"); 
        printLocalizedText("Please restart this program", "�����������˳���"); 
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
    printLocalizedText("Enter the new step:", "�������µļ��㲽����"); 
    printLocalizedText("Tip:the shorter step is,the more time cost", "��ʾ������Խ�̣�����ʱ��Խ��"); 
    printLocalizedText("Recommended value:0.1", "����ֵ��0.1"); 
    cin >> newStep; 

    // Update the global variable
    step = newStep;

    ofstream outFileStep("config_Step.ini"); // Changed filename to config_ecd.ini
    if (outFileStep.is_open()) { 
        outFileStep << "Step: " << newStep << ".\n"; 
        outFileStep.close(); 
        printLocalizedText("Step value updated successfully!", "���㲽���ѳɹ����£�"); 
        printLocalizedText("Please restart this program", "�����������˳���"); 
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
    	printLocalizedText("Genshin Impact Max Damage Calculator v2.2.10.74c", "ԭ������˺������� v2.2.10.74c");
        printLocalizedText("1. Calculate maximum damage", "1. ��������˺�");
        printLocalizedText("2. Exit program", "2. �˳�����");
        printLocalizedText("3. Desired CRIT rate(if you used this program)", "3. ���������ʣ������ʹ�ù��˳���");
        printLocalizedText("4. Change language", "4. ��������");
        printLocalizedText("5. Change calculate step(Calculation accuracy)", "5. ���ļ��㲽�������㾫�ȣ�");
        printLocalizedText("Please enter your choice: ", "����������ѡ��");
        cin >> choice;

        switch (choice) {
        case 1:
            calculateMaxDamage(desiredCritRate,step);
            break;
        case 2:
            printLocalizedText("Thank you for using, goodbye!", "��лʹ�ã��ټ���");
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
