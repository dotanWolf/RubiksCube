class Move {
    private:
        int* mask;
        int* diff;
    public:
        Move(int* mask, int* diff);
        int* getMask();
        int* getDiff();
};