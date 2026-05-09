void print_int128(__int128_t x) {
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    if (x > 9) print_int128(x / 10);
    cout << char(x % 10 + '0');
}