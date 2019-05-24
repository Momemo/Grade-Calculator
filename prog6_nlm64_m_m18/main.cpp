/*
 File: prog6_nlm64_m_m18.cpp
 
 Author: Mohammad
 C.S.1428
 
 Listed on an input file is data for a class of 13 students. Each record
 contains a student's ID, daily average and exam average in this order.
 Two parallel arrays are used to store the input data, a string array
 to store the student IDs and a real array to store the daily and exam
 averages. After storing the input data in to the respective arrays, the
 semester averages are calculated for each student and the results stored
 in the array of averages. The semester averages are then used to
 determine the associated letter grade for each student. The results
 are stored in a third parallel array. A grade report is generated and
 printed to an output file.
 
 This program uses those functions described below. Classes are not used
 in the solution. Array dimensions and column references are the only
 global variables used.
 
 Input(file - prog6_?inp.txt):
 multiple records, three data items per record, in this order:
 student ID (string)   daily asg avg (double)    exam avg (double)
 
 Constants:
 GLOBAL constants:
 
 int STUDENTS = 13,   // number of students
 AVGS = 3;        // number of averages
 
 int DAILY_AVG = 0,   // col in which daily averages are stored
 EXAM_AVG = 1,    // col in which exam averages are stored
 SMST_AVG = 2;    // col in which semester averages are stored
 
 LOCAL constants in main:
 
 string AUTHORS = " ... ",      // team members, team leader first
 DUE_DATE = "--/--/--",  // due date
 LAB_SECTION = "L??";    // 2 digit lab section numbers
 
 int LECTURE_SECTION = ?,       // 3 digit lecture section number
 MAX_LENGTH_FN = 20;        // maximum length for file names
 
 double GRD_A = 89.5,
 GRD_B = 79.5,
 GRD_C = 69.5,
 GRD_D = 59.5;
 
 int DAILY_ASG_PERCENTAGE = 3;    // daily avg on a 10 pt scale
 double EXAM_AVG_PERCENTAGE = .7; // exam avg on a 100 pt scale
 
 Output(console):  (Sample Console Output)
 
 Authors' Names
 C.S.1428.?
 Lab Section: L??
 --/--/--
 <blank line>
 The student grade report has been processed and saved to prog6_?out.txt.
 
 Output (file - prog6_?out.txt):
 
 Sample file output:
 
 Authors' Names
 C.S.1428.?
 Lab Section: L??
 --/--/--
 <blank line>
 SEMESTER GRADE REPORT
 <blank line>
 Student     Semester   Letter
 ID        Average    Grade
 -------------------------------
 A00123456     90.39       A
 A00234567     86.92       B
 ...
 
 ======================================================================
 
 The program is processed as follows:
 
 * A void function, readData, reads the input data into two parallel
 arrays, one that holds the student IDs and one that holds the daily
 assignment and exam averages.
 Note: The 'averages' array will eventually hold the semester averages
 as well.
 * A void function, calcSemesterAvg, calculates the semester averages,
 storing the results in the array of averages previously created.
 
 The semester average is calculated as follows:
 Daily assignment average 30%
 Exam average 70%
 Note: The semester average calculation allows for the fact that the
 daily assignment averages are posted on a 10% scale and the
 exam averages on a 100% scale.
 * A void function, determineLtrGrd, determines the letter grades that
 will be assigned for the semester and stores the results in a character
 array. The letter grade is determined based on the following:
 'A' -- 89.5 or higher
 'B' -- 79.5 or greater but less than 89.5
 etc.
 * A void function, printGradeReportHeadings, prints to the output file
 an appropriate title and column headers for a semester grade report.
 * A typed function, getPrecision, prompts the user for the number of
 decimal places he/she wishes to display on the student grade report.
 The user's response is returned to the calling routine. getPrecision
 leaves two blank lines after the prompt/keyboard response is displayed.
 * A void function, printGradeReport, prints IDs, semester averages and
 assigned letter grades under appropriate column headers.
 * A void function, printIdInfo, prints the authors' personal information
 (name, class/section number, lab section number(s), due date) on the
 first, second, third and fourth lines. The fifth line is left blank. The
 calling routine determines the output stream to which the information is
 directed.
 * A void function, printOutputFileNotice, writes to the console one
 blank line followed by a notice to users that the student information
 has been processed and stored to an output file. The name of the
 output file is provided by the calling routine and is included in the
 console notification.
 
 ======================================================================
 
 Notes:
 - The user determines the number of decimal places to which the averages
 are displayed. Semester averages are formatted to two decimal
 places for the final report run.
 - Student records are single-spaced on the output file.
 - All functions are fully documented.
 
 =======================================================================
 
 <Output will vary based on actual input.>
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int STUDENTS = 13,
AVGS = 3;

const int DAILY_AVG = 0,
EXAM_AVG = 1,
SMST_AVG = 2;

void readData ( ifstream &fin, string student_ids [],
               double averages [] [AVGS] );
void calcSemesterAvg ( double averages [] [AVGS], const int DAILY_ASG_PERCENTAGE,
                      const double EXAM_AVG_PERCENTAGE );
void determineLtrGrd ( double averages [] [AVGS], char ltr_grds [ ],
                      const double GRD_A, const double GRD_B,
                      const double GRD_C,const double GRD_D );
void printGradeReportHeadings ( ofstream &fout );
void printIdInfo ( ostream &fout, const string AUTHORS,
                  const int LECTURE_SECTION,const string LAB_SECTION,
                  const string DUE_DATE ) ;
int getPrecision ( );
void printGradeReport ( ofstream &fout, const double averages [] [AVGS],
                       string student_ids[], char ltr_grds [ ], int places );
void printOutputFileNotice ( char output_filename [] );

int main ( )
{
    const string AUTHORS = "Mohammad Memon",
    DUE_DATE = "04/25/18",
    LAB_SECTION = "L49, L49";
    
    const int LECTURE_SECTION = 301,
    MAX_LENGTH_FN = 20;
    
    const double GRD_A = 89.5,
    GRD_B = 79.5,
    GRD_C = 69.5,
    GRD_D = 59.5;
    
    const int DAILY_ASG_PERCENTAGE = 3;
    const double EXAM_AVG_PERCENTAGE = 0.7;
    
    string student_ids[STUDENTS];
    double averages[STUDENTS][AVGS];
    char   ltr_grds[STUDENTS];
    
    int places;
    
    char input_filename[MAX_LENGTH_FN + 1] = "prog6_301inp.txt",
    output_filename[MAX_LENGTH_FN + 1] = "prog6_301out.txt";
    
    ifstream fin;
    fin.open ( input_filename );
    
    if ( !fin )
    {
        cout << "Input file failed to open" << endl
        << "Terminating program" << endl;
        
        
        return 1;
    }
    
    ofstream fout;
    fout.open ( output_filename );
    
    if ( !fout )
    {
        cout << "Output file failed to open" << endl
        << "Terminating program";
        
        fin.close ( );
        
        
        return 2;
    }
    
    readData ( fin, student_ids, averages );
    calcSemesterAvg ( averages, DAILY_ASG_PERCENTAGE, EXAM_AVG_PERCENTAGE );
    determineLtrGrd ( averages, ltr_grds, GRD_A, GRD_B, GRD_C, GRD_D );
    printIdInfo ( fout, AUTHORS,  LECTURE_SECTION,   LAB_SECTION,  DUE_DATE );
    printGradeReportHeadings ( fout );
    places = getPrecision ( );
    printGradeReport ( fout, averages, student_ids, ltr_grds, places);
    printIdInfo ( cout, AUTHORS,  LECTURE_SECTION,   LAB_SECTION,  DUE_DATE );
    printOutputFileNotice ( output_filename );
    
    fin.close ( );
    fout.close ( );
    
    
    return 0;
}

/*
 Function: readData
 
 Author:  Mohammad

 
 
 The function, readData, reads the input data into two parallel arrays,
 one that holds the student IDs and one that holds the daily assignment
 and exam averages.
 Note: The ëaveragesí array will eventually hold the semester averages
 as well.
 
 Receives: fin, student_ids, averages
 Constants: Nothing
 Returns: Nothing
 */

void readData ( ifstream &fin, string student_ids [],
               double averages [] [AVGS] )
{
    for ( int i = 0; i < STUDENTS ; i++ )
        fin >> student_ids [i]
        >> averages [i] [DAILY_AVG]
        >> averages [i] [EXAM_AVG];
}

/*
 Function: calcSemesterAvg
 
 Author: Mohammad
 C.S.1428.301
 
 The function, calcSemesterAvg, calculates semester averages, storing the
 results in the array of averages previously created.
 The semester average is calculated as follows:
 Daily assignment average 30%
 Exam average 70%
 
 Receives: averages, DAILY_ASG_PERCENTAGE, EXAM_AVG_PERCENTAGE
 Constants: DAILY_ASG_PERCENTAGE, EXAM_AVG_PERCENTAGE
 Returns: Semester averages
 */

void calcSemesterAvg ( double averages [] [AVGS], const int DAILY_ASG_PERCENTAGE,
                      const double EXAM_AVG_PERCENTAGE )
{
    for ( int i = 0; i < STUDENTS ; i++ )
        averages [i] [SMST_AVG] = ( DAILY_ASG_PERCENTAGE *
                                   averages[i][DAILY_AVG] ) +
                                  ( averages[i][EXAM_AVG] *
                                    EXAM_AVG_PERCENTAGE );
}

/*
 Function: determineLtrGrd
 
 Author:  Mohammad
 C.S.1428
 
 The function, determineLtrGrd, determines the letter grades that will be
 assigned for the semester, storing the results in a character array.
 The letter grade should be determined based on the following:
 ëAí -- 89.5 or higher
 ëBí -- 79.5 or greater but less than 89.5
 etc.
 
 Receives: averages, ltr_grds, GRD_A, GRD_B, GRD_C, GRD_D
 Constants: GRD_A, GRD_B, GRD_C, GRD_D
 Returns: Nothing
 */

void determineLtrGrd ( double averages [] [AVGS], char ltr_grds [ ],
                      const double GRD_A, const double GRD_B,
                      const double GRD_C,const double GRD_D )
{
    for ( int i = 0; i < STUDENTS; i++ )
        if ( ( averages [i][SMST_AVG] >= GRD_A ) )
            ltr_grds[i] = 'A';
        else if ( ( averages [i][SMST_AVG] >= GRD_B ) )
            ltr_grds[i] = 'B';
        else if ( ( averages[i][SMST_AVG] >= GRD_C ) )
            ltr_grds[i] = 'C';
        else if ( ( averages[i][SMST_AVG] >= GRD_D ) )
            ltr_grds[i] = 'D';
        else
            ltr_grds [i] = 'F';
}

/*
 Function: printIdInfo
 
 Author: Mohammad
 C.S.1428
 
 The function, printIdInfo, that prints the authorsí personal
 information (name, class/section number, lab section number, due date) on
 the first, second, third and fourth lines. The fifth line is left blank.
 The calling routine determines the output stream to which the information
 is directed.) See notes below. Used to print in the output file and the
 screen.
 
 Receives: ostream &fout, AUTHORS,  LECTURE_SECTION,   LAB_SECTION,  DUE_DATE
 Constants: AUTHORS,  LECTURE_SECTION,   LAB_SECTION,  DUE_DATE
 Returns: Nothing
 */

void printIdInfo ( ostream &fout, const string AUTHORS,
                  const int LECTURE_SECTION,const string LAB_SECTION,
                  const string DUE_DATE )
{
    fout << AUTHORS << endl
    <<"C.S.1428." << LECTURE_SECTION << endl
    <<"Lab Section: " << LAB_SECTION << endl
    << DUE_DATE << endl << endl;
}

/*
 Function: printGradeReportHeadings
 
 Author:  Mohammad
 C.S.1428

 The function, printGradeReportHeadings, to print to the output file an
 appropriate title and column headers for a semester grade report.
 
 Receives: ofstream &fout
 Constants: AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE
 Returns: Nothing
 */

void printGradeReportHeadings ( ofstream &fout )
{
    fout << "            Semester Grade Report                        "
    << endl << endl
    << "Student           Semester         Letter " << endl
    << "  ID              Average          Grade  " << endl
    << "-----------------------------------------------"
    << endl;
}

/*
 Function: getPrecision
 
 Author:  Mohammad
 C.S.1428
 
 The function, getPrecision, prompts the user for the number of decimal
 places he/she wishes to display on the student grade report. The userís
 response is returned to the calling routine. getPrecision leaves two blank
 lines after the prompt/keyboard response is displayed.
 
 Receives: Nothing
 Constants: Nothing
 Returns: places
 */


int getPrecision ( )
{
    int places;
    
    cout << "Enter the number of decimal places you would like to display: ";
    cin  >> places;
    cout << endl<< endl;
    
    return places;
}

/*
 Function: printGradeReport
 
 Author:  Mohammad
 C.S.1428
 
 The function, printGradeReport, prints IDs, semester averages and
 letter grades assigned under the appropriate column headers.
 
 Receives: fout, averages, student_ids, ltr_grds, places
 Constants: Nothing
 Returns: Nothing
 */

void printGradeReport ( ofstream &fout, const double averages [] [AVGS],
                       string student_ids[], char ltr_grds [ ], int places )
{
    fout << fixed << setprecision (places);
    
    for ( int i = 0; i < STUDENTS ; i++ )
        fout << student_ids [i]  << "          "
        << averages [i] [SMST_AVG]
        <<  "             " << ltr_grds [i] << endl;
}

/*
 Function: printOutputFileNotice
 
 Author:  Mohammad
 C.S.1428
 
 The function, printOutputFileNotice, prints IDs, semester averages and
 letter grades assigned under the appropriate column headers.
 
 Receives: char output_filename
 Constants: Nothing
 Returns: Nothing
 */

void printOutputFileNotice ( char output_filename [] )
{
    cout << endl
         << "Student grade report has been processed and saved to "
        << output_filename << endl;
}


