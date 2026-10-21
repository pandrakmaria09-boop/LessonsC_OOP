#include <iostream>
using namespace std;

class Time
{
    int h;
    int m;
    int s;
public:
    Time()
    {
        h = m = s = 0;
    }
    Time(int h, int m, int s)
    {
        this->h = h;
        this->m = m;
        this->s = s;
    }
    //5555/3600 - h; 5555/60%60 - m; 5555%60 - s
    explicit Time(int seconds)
    {
        this->h = seconds / 3600;
        this->m = seconds / 60 % 60;
        this->s = seconds % 60;
    }
    void Print()
    {
        if (h < 10) cout << "0";
        cout << h << ":";
        if (m < 10) cout << "0";
        cout << m << ":";
        if (s < 10) cout << "0";
        cout << s << endl;
    }
   
    int ToSeconds() const
    {
        return h * 3600 + m * 60 + s;
    }

    void PlusSecond()
    {
        s++;
        if (s == 60)
        {
            s = 0;
            m++;
        }
        if (m == 60)
        {
            m = 0;
            h++;
        }
        if (h == 24)
        {
            h = 0;
        }
    }

#pragma region Математичні оператори
    Time operator +(const Time& other) const
    {
        Time res(this->ToSeconds() + other.ToSeconds());
        return res;
    }
    Time operator -(const Time& other) const
    {
        int sec = this->ToSeconds() - other.ToSeconds();
        if (sec < 0)
        {
            sec = 0;
        }
        Time res(sec);
        return res;
    }
    Time operator *(const Time& other) const
    {
        Time res(this->ToSeconds() * other.ToSeconds());
        return res;
    }
    Time operator /(const Time& other) const
    {
        if (other.ToSeconds() == 0)
        {
            cout << "Division by zero!" << endl;
            return Time();
        }
        Time res(this->ToSeconds() / other.ToSeconds());
        return res;
    }
#pragma endregion

#pragma region Logic operators  < > <= >= == !=
    bool operator >(const Time& other) const
    {
        return this->ToSeconds() > other.ToSeconds();
    }
    bool operator <(const Time& other) const
    {
        return this->ToSeconds() < other.ToSeconds();
    }
    bool operator >=(const Time& other) const
    {
        return this->ToSeconds() >= other.ToSeconds();
    }
    bool operator <=(const Time& other) const
    {
        return this->ToSeconds() <= other.ToSeconds();
    }
    bool operator ==(const Time& other) const
    {
        return this->ToSeconds() == other.ToSeconds();
    }
    bool operator !=(const Time& other) const
    {
        return this->ToSeconds() != other.ToSeconds();
    }
#pragma endregion
};

int main()
{
    Time t1;
    Time t2(1, 30, 15);
    Time t3(5555);//5555 = 1год 32хв 35сек
    Time t4(11, 59, 59);

    cout << "Time 1 : "; t1.Print();
    cout << "Time 2 : "; t2.Print();
    cout << "Time 3 : "; t3.Print();
    cout << "------------------------" << endl;

    cout << "Time 4 : "; t4.Print();
    t4.PlusSecond();
    cout << "Time 4 + 1 sec : "; t4.Print();
    cout << "------------------------" << endl;

    Time res = t2 + t3;
    cout << "t2 + t3 : "; res.Print();

    res = t3 - t2;
    cout << "t3 - t2 : "; res.Print();

    res = t2 - t3;
    cout << "t2 - t3 : "; res.Print();

    res = t2 * Time(0, 0, 2);
    cout << "t2 * 2 sec : "; res.Print();

    res = t3 / Time(0, 0, 5);
    cout << "t3 / 5 sec : "; res.Print();
    cout << "------------------------" << endl;

    cout << "t2 > t3  : " << (t2 > t3) << endl;
    cout << "t2 < t3  : " << (t2 < t3) << endl;
    cout << "t2 >= t3 : " << (t2 >= t3) << endl;
    cout << "t2 <= t3 : " << (t2 <= t3) << endl;
    cout << "t2 == t3 : " << (t2 == t3) << endl;
    cout << "t2 != t3 : " << (t2 != t3) << endl;

    Time t5(5400);//1:30:00
    Time t6(1, 30, 0);
    cout << "t5 == t6 : " << (t5 == t6) << endl;
    cout << "t5 != t6 : " << (t5 != t6) << endl;
}