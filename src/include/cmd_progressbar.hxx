#ifndef CMD_PROGRESSBAR_H__
#define CMD_PROGRESSBAR_H__

#ifndef CPB_API
	#define CPB_API
#endif

#ifndef CPB_ASSERT
    #define  CPB_ASSERT(expression, description) assert(expression)                          
#endif

#include <iostream>
#include <ostream>
#include <string>
#include <cassert>

namespace cpb{

class bar
{
public:
    inline  bar();
    inline  bar(int n, bool showbar = true, std::ostream &out = std::cout);
            ~bar() = default;
            bar(bar const &) = delete;
            bar &operator=(bar const &) = delete;
            bar(bar &&) = delete;
            bar &operator=(bar &&) = delete;
public:
    CPB_API inline void     render()                                {update();m_progress++;}// core render function
    CPB_API inline bar&     reset();
    CPB_API inline bar&     during(const int num_steps);// set number of steps
    CPB_API inline bar&     done_via(const std::string &sym)        { m_chDone = sym; return *this; }// chose your own style
    CPB_API inline bar&     go_via(const std::string &sym)          { m_chGo = sym; return *this;}
    CPB_API inline bar&     start_via(const std::string &sym)       { m_chStart = sym; return *this;}
    CPB_API inline bar&     end_via(const std::string &sym)         { m_chEnd = sym;return *this; }
    CPB_API inline bar&     pos_via(const std::string &sym)         { m_chPos = sym; return *this;}
    CPB_API inline bar&     width_via(const int width)              { m_barWidth = width;return *this; }
    CPB_API inline bar&     output_via(const std::ostream &stream)  { m_output.rdbuf(stream.rdbuf());return *this; }// set the output stream
    CPB_API inline bar&     is_showbar(bool flag = true)            { m_is_show_bar = flag; return *this;}// to show only the percentage
private:
    inline void     update();
private:
    int                         m_progress;
    int                         m_steps;
    int                         m_barWidth;
    int                         m_last_percent;
    int                         m_current_percent;
    bool                        m_is_show_bar;

    std::string                 m_chDone;
    std::string                 m_chGo;
    std::string                 m_chPos;
    std::string                 m_chStart;
    std::string                 m_chEnd;
    std::ostream                &m_output;

};
inline bar::bar() : m_progress{0},              m_steps{100},           m_last_percent{0},          m_current_percent{0},      
                    m_barWidth{70},             m_is_show_bar{true},    m_chDone{"#"},              m_chGo{" "},
                    m_chPos{">"},               m_chStart{"["},         m_chEnd{"]"},               m_output{std::cout}{}

inline bar::bar(int n, bool showbar, std::ostream &out) :   m_progress{0},          m_steps{n},     m_last_percent{0},
                                                            m_current_percent{0},   m_barWidth{70}, m_is_show_bar{showbar},
                                                            m_chDone{"#"},          m_chGo{" "},    m_chPos{">"},               
                                                            m_chStart{"["},         m_chEnd{"]"},   m_output{out}{}
inline bar& bar::reset()
{
    m_progress = 0, m_last_percent = 0, m_current_percent = 0;
    return *this;
}
inline bar& bar::during(const int num_steps)
{
    CPB_ASSERT(num_steps > 0,"number of steps null or negative");
    m_steps = num_steps;
    return *this;
}
inline void bar::update()
{
    CPB_ASSERT(m_steps != 0, "number of steps not set");
    m_current_percent = m_progress * 100. / (m_steps - 1);
    if(m_is_show_bar){
        int pos = m_barWidth * (static_cast<float>(m_current_percent)/100.0f);
        m_output << m_chStart;
        for (int i = 0; i < m_barWidth; ++i){
            if (i < pos)        m_output << m_chDone;
            else if (i == pos)  m_output << m_chPos;
            else                m_output << m_chGo;
        }
        m_output << m_chEnd << ' ' << m_current_percent << " %\r";
    }else{
        m_output << m_current_percent << " %\r";
    }
    m_output << std::flush;    
    m_last_percent = m_current_percent;
}

} //end cpb
#endif