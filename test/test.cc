#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <thread>

#include "cmd_progressbar.hxx"

void testCase1(){
    int N = 100;

    cpb::bar testbar(N);

    for ( int i = 0; i < N; i++ ) {

        testbar.render();

        // mock the program 
        std::this_thread::sleep_for( std::chrono::microseconds(300) );
    }

    std::cerr << std::endl;
}

//change style
void testCase2(){
    int N = 200;
    cpb::bar testbar;
    testbar.during(N);
    testbar.reset();
    testbar.go_via(" ");
    testbar.done_via("█");
    testbar.pos_via("@");
    testbar.start_via("{");
    testbar.end_via("}");
    for ( int i = 0; i < N; i++ ) {

        testbar.render();
        std::this_thread::sleep_for( std::chrono::microseconds(300) );
    }

    std::cerr << std::endl;
}

// dont show bar
void testCase3(){
    int N = 200;
    cpb::bar testbar;
    testbar.during(N);
    testbar.reset();
    testbar.is_showbar(false);
    for ( int i = 0; i < N; i++ ) {

        testbar.render();
        std::this_thread::sleep_for( std::chrono::microseconds(300) );
    }
    std::cerr << std::endl;

    testbar.reset();
    testbar.is_showbar(true);
    testbar.output_via(std::cerr);
    for ( int i = 0; i < N; i++ ) {

        testbar.render();
        std::this_thread::sleep_for( std::chrono::microseconds(300) );
    }

    std::cerr << std::endl;
}

// multi threads
void testCase4(){
    int N = 200;
    cpb::bar testbar(N);
    std::atomic<int> i{0};
    std::mutex m;
    auto lamd = [&m,&i,&N,&testbar](){
                    while(true) {
                        std::lock_guard<std::mutex> lg(m);
                        if(i<N){   
                            testbar.render();
                            i++; 
                            std::this_thread::sleep_for( std::chrono::microseconds(300) );
                        }else{
                            break;
                        }
                    }
    };        
    auto t1 = std::thread(lamd);
    auto t2 = std::thread(lamd);
    auto t3 = std::thread(lamd);

    t1.join();
    t2.join();
    t3.join();
    

    std::cerr << std::endl;
}

int main() {

    testCase1();
    testCase2();
    testCase3();
    testCase4();

    return 0;
}