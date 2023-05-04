#pragma once

#include "_str.h"

class Str {
    _str *m_pStr;
public:
    inline Str() { m_pStr = new _str; }        //если не копия, то создаем
    inline Str(const char *p) {        // новый ресурс
        m_pStr = new _str(p);
    }

    Str(const Str &s);

    inline ~ Str() {
        m_pStr->Release();    // Не уничтожаем ресурс!
    }                // Уменьшаем счетчик ссылок!
    int len() const {
        return strlen(m_pStr->m_pszData);
    }

    int rfind(const char *t, int off);

    operator const char* () const {return m_pStr->m_pszData;}

    Str &operator=(const Str &s);

    Str &operator+=(const Str &s);

};

Str::Str(const Str &s){
    m_pStr = s.m_pStr;    // ссылаемся на тот же ресурс
    m_pStr->AddRef();    // отмечаем, что сослались
}

//Присваивание образует выражение!
Str &Str::operator=(const Str &s) {
    if (this != &s) {
        s.m_pStr->AddRef(); // Важен порядок?!
        m_pStr->Release();
        m_pStr = s.m_pStr;
    }
    return *this;
}

Str &Str::operator+=(const Str &s) {
    int length = len() + s.len();
    if (s.len() != 0) {        // добавление ничего не изменит!
        _str *pstrTmp = new _str;    // Новый ресурс
        delete[] pstrTmp->m_pszData;

        pstrTmp->m_pszData = new char[length + 1];
        std::strcpy(pstrTmp->m_pszData, m_pStr->m_pszData);
        std::strcat(pstrTmp->m_pszData, s.m_pStr->m_pszData);

        m_pStr->Release();
        m_pStr = pstrTmp;
    }
    return *this;
}

//last occurrence in the string
int Str::rfind(const char *t, int off){
    char *curr_based = m_pStr->m_pszData + off;

    const char *qwe = t;
    char *curr_finding = new char[strlen(qwe)];
    std::strcpy(curr_finding, qwe);
    curr_finding = curr_finding + strlen(t) - 1;

    int len_t = strlen(t);
    if (strlen(t) > strlen(m_pStr->m_pszData) || strlen(t) == 0){
        return -1;
    }
    while(curr_based != m_pStr->m_pszData - 1){
        char *i = curr_based;
        char *j = curr_finding;
        int count = 0;
        while (*i == *j && count != len_t){
            count ++;
            i--;
            j--;
        }
        if (count == len_t){
            return i - m_pStr->m_pszData + 1;
        }
        curr_based--;
    }
    return -1;
}

