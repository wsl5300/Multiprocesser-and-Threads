# include <stdio.h>
# include <stdlib.h>
# include <fstream>
# include <iostream>
#include <algorithm>
# include <vector>
# include <string>
# include <chrono>
# include <time.h>
# include <cmath>
# include <unistd.h>
# include <thread>
# include <sys/types.h>
# include <sys/wait.h>
# include <mutex>
using namespace std ;


vector < vector<int> > buffer ;
      vector <int> temp ;
      clock_t START, END ;
      double TEMP ;
      int gnum = 0 ;



  void swap( int m, int a, int b ) {
    int temp ;
    temp = buffer[m][a] ;
    buffer[m][a] = buffer[m][b] ;
    buffer[m][b] = temp ;
    return ;
  } // swap()

  void BubbleSort( int m ) { // m_buffer從a排到b

    for ( int i = buffer[m].capacity() - 1 ; i > 0 ; i-- ) {
      for( int j = 0; j <= i-1; j++){
        if( buffer[m][j] > buffer[m][j+1]) swap( m, j, j+1 ) ;
      }
    }

  } // BubbleSort()

  void split( int k ) { // 將temp切成k份放在二維vector中
    int n = temp.size()-1;
    int len = n / k ;
    buffer.resize(k);
    for (int i = 0; i < k; i++) {
        int start = i * len;
        int end = (i == k - 1) ? n : (i + 1) * len;
        buffer[i].assign(temp.begin() + start, temp.begin() + end);
    } // for

  } // split()

  void Merge4( int i, int j, int m ) { // 兩串合併到第gnum串上

    int a=0, b=0 ;
    vector <int> stemp ;
    if ( j >= m ) {
      return ;
    } // if
    else {
      while ( a < buffer[i].size() || b < buffer[j].size() ) {
        if ( a >= buffer[i].size() ) {
          for ( ; b < buffer[j].size() ; b++ ) stemp.push_back(buffer[j][b]) ;
          break ;
        } // if

        if ( b >= buffer[j].size() ) {
          for ( ; a < buffer[i].size() ; a++ ) stemp.push_back(buffer[i][a]) ;
          break ;
        } // if

        if ( buffer[i][a] <= buffer[j][b] ) {
          stemp.push_back(buffer[i][a]) ;
          a++ ;
        } // if
        else {
          stemp.push_back(buffer[j][b]) ;
          b++ ;
        } // else

      } // while

      buffer[i].clear() ;
      buffer[j].clear() ;
      buffer[i].assign( stemp.begin(), stemp.end() ) ;

    } // else
    return ;


  } // merge




    void mission4( string filename, int k ) {

      int a = 0 ; // file temp
      int m = 0 ; // mergesort
      ifstream file ;
      string filen = filename ;
      filename = filename + ".txt" ;
      file.open( filename.c_str(), ios::in ) ;
      if ( !file.is_open()) {
        cout << "unfound file" << endl ;
        return ;
      } // if
      for ( int i = 0 ; file.good() ; i++ ) {
        file >> a ;
        temp.push_back(a) ;
      } // for

      file.close() ;
      split(k) ; // 把temp分成 k 份裝進buffer
      temp.clear();

      START = clock();
      vector <thread> th(k) ;

      for ( int i = 0 ; i < k ; i++ ) {
        th[i] = thread( BubbleSort, i ) ;
        //return 0 ;
      } // for

      for ( int i = 0 ; i < k ; i++ ) {
        th[i].join() ;
      } // for

      cout << "*******" << endl ;

      int i = 0 ;
      int num = 0 ; // ......
      int p = 0 ;
      int temp = p ;
      vector <thread> ths(k-1) ;
      for ( float m = buffer.size() ; m > 1 ; m = ceil( m / 2 ) ) {
          num++ ;
          i = 0 ;
          temp = p ;
          for ( int j = pow(2,num-1) ; i < k ; j = j + pow(2,num) ) {
            if ( j >= k ) break;
            else {
              ths[p] = thread(Merge4, i, j, k ) ;
              //Merge( i, j, k) ;
              //ths[p].join() ;
              p++ ;
              i = i + pow(2,num) ;
              //gnum = i ;
            } // else
          } // for

          for ( int i = temp ; i < p ; i++ ) {
            if ( ths[i].joinable() ) ths[i].join() ;
          } // for

          gnum = 0 ;


      } // for

      END = clock() ;
      TEMP = (double)END - START ;
      cout << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;

//////////////////////////////////////////////////////////////////

      filename = filen + "_output4.txt"  ;
      ofstream out ( filename.c_str(), ios::out|ios::trunc ) ;

	  if (out.is_open()) {
		for ( int i = 0 ; i < buffer[0].size() ; i++ ) {
          out << buffer[0][i] << endl ; // 寫入數字到檔案，以空格分隔
        }

        time_t now = time(nullptr) ;
        time_t utc8 = mktime(gmtime(&now)) + 8 * 3600 ;
		char nowtime[80] ;
		strftime(nowtime, 80, "%Y-%m-%d %H:%M:%S", localtime(&utc8));

        out << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;
        out << "Output Time : " << nowtime  << endl ;
        out.close(); // 關閉檔案
      } // if
      else {
        cout << "Unable to open file\n";
      }

      buffer[0].clear() ;
      buffer.clear() ;

    } // mission4()

class Sort {
  vector < vector<int> > buffer ;
  vector <int> temp ;
  clock_t START, END ;
  double TEMP ;
  int gnum = 0 ;

public:
  void swap( int m, int a, int b ) {
    int temp ;
    temp = buffer[m][a] ;
    buffer[m][a] = buffer[m][b] ;
    buffer[m][b] = temp ;
    return ;
  } // swap()

  void BubbleSort( int m ) { // m_buffer從a排到b

    for ( int i = buffer[m].capacity() - 1 ; i > 0 ; i-- ) {
      for( int j = 0; j <= i-1; j++){
        if( buffer[m][j] > buffer[m][j+1]) swap( m, j, j+1 ) ;
      }
    }

  } // BubbleSort()

  void split( int k ) { // 將temp切成k份放在二維vector中
    int n = temp.size()-1;
    int len = n / k ;
    buffer.resize(k);
    for (int i = 0; i < k; i++) {
        int start = i * len;
        int end = (i == k - 1) ? n : (i + 1) * len;
        buffer[i].assign(temp.begin() + start, temp.begin() + end);
    } // for

  } // split()

  void Merge( int i, int j, int m ) { // 兩串合併到第gnum串上

    int a=0, b=0 ;
    vector <int> stemp ;
    if ( j >= m ) {
      buffer[gnum].clear() ;
      buffer[gnum].assign( buffer[i].begin(), buffer[i].end() ) ;
      buffer[i].clear() ;
    } // if
    else {
      while ( a < buffer[i].size() || b < buffer[j].size() ) {
        if ( a >= buffer[i].size() ) {
          for ( ; b < buffer[j].size() ; b++ ) stemp.push_back(buffer[j][b]) ;
          break ;
        } // if

        if ( b >= buffer[j].size() ) {
          for ( ; a < buffer[i].size() ; a++ ) stemp.push_back(buffer[i][a]) ;
          break ;
        } // if

        if ( buffer[i][a] <= buffer[j][b] ) {
          stemp.push_back(buffer[i][a]) ;
          a++ ;
        } // if
        else {
          stemp.push_back(buffer[j][b]) ;
          b++ ;
        } // else

      } // while

      buffer[i].clear() ;
      buffer[j].clear() ;
      buffer[gnum].assign( stemp.begin(), stemp.end() ) ;

    } // else


  } // merge


    void mission1( string filename ) {
      int a = 0 ;
      ifstream file ;
      string filen = filename ;
      filename = filename + ".txt" ;
      file.open( filename.c_str(), ios::in ) ;
      if ( !file.is_open()) {
        cout << "unfound file" << endl ;
        return ;
      } // if
      for ( int i = 0 ; file.good() ; i++ ) {
        file >> a ;
        temp.push_back(a) ;
      } // for

      split(1) ;
      temp.clear() ;
      file.close() ;

      START = clock();

      BubbleSort( 0 ); // 排序buffer[0]的陣列

      END = clock();
      TEMP = (double)END - START ;
      cout << "CPU time : " << TEMP / CLOCKS_PER_SEC << " s"<< endl ;

      filename =  filen +  "_output1.txt" ;
	  ofstream out ( filename.c_str(), ios::out|ios::trunc ) ;

	  if (out.is_open()) {
        for ( int i = 0 ; i < buffer[0].size() ; i++ ) {
            out << buffer[0][i] << endl ; // 寫入數字到檔案，以空格分隔
        }

        time_t now = time(nullptr) ;
        time_t utc8 = mktime(gmtime(&now)) + 8 * 3600 ;
		char nowtime[80] ;
		strftime(nowtime, 80, "%Y-%m-%d %H:%M:%S", localtime(&utc8));

        out << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;
        out << "Output Time : " << nowtime  << endl ;
        out.close(); // 關閉檔案
      } // if
      else {
        cout << "Unable to open file\n";
      }

			buffer[0].clear() ;



    } // mission1()

    void mission2( string filename, int k ) {
      int a = 0 ;
      int m = 0 ;
      ifstream file ;
      string filen = filename ;
      filename = filename + ".txt" ;
      file.open( filename.c_str(), ios::in ) ;
      if ( !file.is_open()) {
        cout << "unfound file" << endl ;
        return ;
      } // if
      for ( int i = 0 ; file.good() ; i++ ) {
        file >> a ;
        temp.push_back(a) ;
      } // for

      file.close() ;
      split(k) ; // 把temp分成 k 份裝進buffer
      temp.clear();

      START = clock();

      for ( int i = 0 ; i < buffer.size() ; i++ ) {
        BubbleSort(i) ;
      } // for

      int i = 0 ;
      for ( float m = buffer.size() ; m > 1 ; m = ceil( m / 2 ) ) {
        i = 0 ;
        for ( int j = 1 ; i < m ; j = j + 2 ) {
          Merge( i, j, m ) ;
          if ( j >= m ) break ;
          i = j + 1 ;
          gnum++ ;
        } // for
        gnum = 0 ;
      } // for

      END = clock() ;
      TEMP = (double)END - START ;
      cout << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;

//////////////////////////////////////////////////////////////////

      filename = filen + "_output2.txt" ;
      ofstream out ( filename.c_str(), ios::out|ios::trunc ) ;

	  if (out.is_open()) {
		for ( int i = 0 ; i < buffer[0].size() ; i++ ) {
          out << buffer[0][i] << endl ; // 寫入數字到檔案，以空格分隔
        }

        time_t now = time(nullptr) ;
        time_t utc8 = mktime(gmtime(&now)) + 8 * 3600 ;
		char nowtime[80] ;
		strftime(nowtime, 80, "%Y-%m-%d %H:%M:%S", localtime(&utc8));

        out << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;
        out << "Output Time : " << nowtime  << endl ;
        out.close(); // 關閉檔案
      } // if
      else {
        cout << "Unable to open file\n";
      }

      buffer[0].clear() ;
      buffer.clear() ;

    } // mission2()

    void mission3( string filename, int k, pid_t &pid ) {
      int a = 0 ; // file temp
      int m = 0 ; // mergesort
      ifstream file ;
      string filen = filename ;
      filename = filename + ".txt" ;
      file.open( filename.c_str(), ios::in ) ;
      if ( !file.is_open()) {
        cout << "unfound file" << endl ;
        return ;
      } // if
      for ( int i = 0 ; file.good() ; i++ ) {
        file >> a ;
        temp.push_back(a) ;
      } // for

      file.close() ;
      split(k) ; // 把temp分成 k 份裝進buffer
      temp.clear();

      START = clock();


      for ( int i = 0 ; i < buffer.size() ; i++ ) {
        pid = vfork() ;
        if ( pid == 0 ) {
          //cout << "Child process #" << i << " (pid=" << getpid() << ") started." << endl;
          BubbleSort(i) ;
          //cout << "Child process #" << i << " (pid=" << getpid() << ") finished." << endl;
          exit(EXIT_FAILURE);
        } // if

      } // for

      int status ;
      if ( pid == 0 ) return ; ///////////////////////
      for (int i = 0; i < k; i++) {
        wait(&status);
      } // for

      cout << "*******" << endl ;

      int i = 0 ;
      for ( float m = buffer.size() ; m > 1 ; m = ceil( m / 2 ) ) {
        pid = vfork() ;
        if ( pid == 0 ) {
          i = 0 ;
          for ( int j = 1 ; i < m ; j = j + 2 ) {
            Merge( i, j, m ) ;
            if ( j >= m ) break ;
            i = j + 1 ;
            gnum++ ;
          } // for

          exit(EXIT_FAILURE);
        } // if
        gnum = 0 ;
        wait(&status);

      } // for

      END = clock() ;
      TEMP = (double)END - START ;
      cout << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;

//////////////////////////////////////////////////////////////////

      filename = filen + "_output3.txt"  ;
      ofstream out ( filename.c_str(), ios::out|ios::trunc ) ;

	  if (out.is_open()) {
		for ( int i = 0 ; i < buffer[0].size() ; i++ ) {
          out << buffer[0][i] << endl ; // 寫入數字到檔案，以空格分隔
        }

        time_t now = time(nullptr) ;
        time_t utc8 = mktime(gmtime(&now)) + 8 * 3600 ;
		char nowtime[80] ;
		strftime(nowtime, 80, "%Y-%m-%d %H:%M:%S", localtime(&utc8));

        out << "CPU Time : " << TEMP / CLOCKS_PER_SEC << " s" << endl ;
        out << "Output Time : " << nowtime  << endl ;
        out.close(); // 關閉檔案
      } // if
      else {
        cout << "Unable to open file\n";
      }

      buffer[0].clear() ;
      buffer.clear() ;

    } // mission3()


};

int main() {
  int command ;
  Sort test ;
  pid_t pid ;
  string filename ;
  int k ; // 要切成幾分
  while( true ) {
		cout << "*** OS HomeWork 01 : Sort  **" << endl ;
		cout << "* 0. QUIT                  *" << endl ;
		cout << "* 1. BubbleSort            *" << endl ;
		cout << "* 2. Process               *" << endl ;
		cout << "* 3. Multi-Processes       *" << endl ;
		cout << "* 4. Threads               *" << endl ;
		cout << "*************************************" << endl ;
		cout << "filename : " ;
		cin >> filename ;
		cout << "cut number : " ;
		cin >> k ;
		while ( cin.fail() ) {
		  cin.clear() ;
		  cin.ignore() ;
		  cout << "Command does not exist!\ncut number : "  ;
		  cin >> k ;
    } // while
		cout << "\nInput a choice(0, 1, 2, 3, 4):" ;
		cin >> command ;
  	while ( cin.fail() ) {
  	  cin.clear() ;
		  cin.ignore() ;
		  cout << "Command does not exist!\nInput a choice(0, 1, 2, 3): "  ;
		  cin >> command ;
    } // while

    if ( command > 4 || command < 0 ) cout << "Command out of range !" << endl << endl ;
 	else if ( command == 0 ) break ;
  	else if ( command == 1 ) {
  	  test.mission1( filename ) ;
  	} // else if
  	else if ( command == 2 ) {
      test.mission2( filename, k ) ;
	} // else if
	else if ( command == 3 ) {
      test.mission3( filename, k, pid ) ;

	} // else if
	else if ( command == 4 ) {
      mission4( filename, k ) ;
	} // else if

	cout << endl << endl ;

	} // while
} // main()
