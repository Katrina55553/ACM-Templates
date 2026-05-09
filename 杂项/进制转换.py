# k进制 --> 十进制  
def char_to_int(c):  
    if '0' <= c <= '9':  
        return ord(c) - ord('0')  
    if 'A' <= c <= 'F':  
        return ord(c) - ord('A') + 10  
def base_10(s: str, k: int) -> int:  
    res = 0  
    n = len(s)  
    for i in range(n):  
        res = res * k + char_to_int(s[i])  
    return res  
    
# 十进制 --> k进制  
def int_to_char(i):  
    if 0 <= i <= 9:  
        return chr(ord('0') + i)  
    elif 10 <= i <= 15:  
        return chr(ord('A') + i - 10)  
def base_k(s: str, k: int) -> str:  
    s = int(s)  
    res = ''  
    while s > 0:  
        res += int_to_char(s % k)  
        s //= k  
    return res[::-1]  
