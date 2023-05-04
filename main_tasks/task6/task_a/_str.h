#pragma once

#include <cstring>
#include <algorithm>

class _str;        //Предварительная декларация
class _str {
    char *m_pszData;
    int m_nCount;

    friend class Str;    //Дружественный класс или метод
    inline _str() {
        m_pszData = new char[1]{0};
        m_nCount = 1;
    }

    inline explicit _str(const char *p) {
        m_nCount = 1;
        auto n = strlen(p);
        m_pszData = new char[n + 1];
        std::copy(p, p + n + 1, m_pszData);
    }

    inline ~_str() { delete[]m_pszData; }

    void AddRef() { m_nCount++; }    //Удаляет себя v
    void Release() {
        m_nCount--;
        if (m_nCount == 0) delete this;
    }
};
