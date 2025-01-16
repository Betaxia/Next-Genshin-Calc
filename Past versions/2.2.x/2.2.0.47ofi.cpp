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
        outFile << "Language: " << currentLanguage << "\n"; 
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
    printLocalizedText("Enter your character's attack or health value:", "���������Ľ�ɫ�Ĺ���������ֵ��"); 
    cin >> a; 
    printLocalizedText("Enter critical rate (%):", "�����뱩���ʣ�%����"); 
    cin >> cr; 

    if (ecr_local == -1) { 
        printLocalizedText("Enter your desired maximum critical rate (%):", "����������������󱩻��ʣ�%����"); 
        cin >> ecr_local; 
    } else { 
        printLocalizedText("Desired maximum critical rate you expected loaded from file:", "���ļ��м��ص����������󱩻��ʣ�%��Ϊ��"); 
        cout << ecr_local << endl; 
    } 

    printLocalizedText("Enter critical damage (%):", "�����뱩���˺���%����"); 
    cin >> cd; 
    printLocalizedText("Enter base attack or health value:", "�������������������ֵ��"); 
    cin >> ba; 
    printLocalizedText("Enter skill multiplier:", "�����뼼�ܱ��ʣ�"); 
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
    printLocalizedText("Your character's maximum damage can reach:", "���Ľ�ɫ������˺����Դﵽ��"); 
    cout << d * r * 0.01 << endl; 
    printLocalizedText("Your character's rating is: ", "���Ľ�ɫ������Ϊ��"); 
    cout << pr << endl; 
    printLocalizedText("Character's attack or health value at this time:", "��ʱ��ɫ�Ĺ���������ֵΪ��"); 
    cout << aa << endl; 
    printLocalizedText("Character's critical rate is:", "��ɫ�ı�����Ϊ��"); 
    cout << acr << "%" << endl; 
    printLocalizedText("Character's critical damage is:", "��ɫ�ı����˺�Ϊ��"); 
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
    printLocalizedText("Genshin Impact Max Damage Calculator v2.2.0.47ofi-en", "ԭ������˺������� v2.2.0.47ofi-zh");
 
    int choice;
    do {
        printLocalizedText("1. Calculate maximum damage", "1. ��������˺�");
        printLocalizedText("2. Exit program", "2. �˳�����");
        printLocalizedText("3. Desired CRIT rate(if you used this program)", "3. ���������ʣ������ʹ�ù��˳���");
        printLocalizedText("4. Change language", "4. ��������");
        printLocalizedText("Please enter your choice: ", "����������ѡ��");
        cin >> choice;
 
        switch (choice) {
            case 1:
                calculateMaxDamage(desiredCritRate);
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
            default:
                printLocalizedText("Invalid choice, please enter again.", "��Чѡ�����������롣");
        }
    } while (choice != 2);
 
    return 0;
}
