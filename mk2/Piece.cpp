std::vector< std::vector<Vector2> > JLSTZ_OFFSET_DATA(5, std::vector<Vector2>(4));
std::vector< std::vector<Vector2> > I_OFFSET_DATA(5, std::vector<Vector2>(4));
std::vector< std::vector<Vector2> > O_OFFSET_DATA(1, std::vector<Vector2>(4));

void Awake(){
    JLSTZ_OFFSET_DATA[0][0].x = 0;
    JLSTZ_OFFSET_DATA[0][0].y = 0;
    JLSTZ_OFFSET_DATA[0][1].x = 0;
    JLSTZ_OFFSET_DATA[0][1].y = 0;
    JLSTZ_OFFSET_DATA[0][2].x = 0;
    JLSTZ_OFFSET_DATA[0][2].y = 0;
    JLSTZ_OFFSET_DATA[0][3].x = 0;
    JLSTZ_OFFSET_DATA[0][3].y = 0;

    JLSTZ_OFFSET_DATA[1][0].x = 0;
    JLSTZ_OFFSET_DATA[1][0].y = 0;
    JLSTZ_OFFSET_DATA[1][1].x = 1;
    JLSTZ_OFFSET_DATA[1][1].y = 0;
    JLSTZ_OFFSET_DATA[1][2].x = 0;
    JLSTZ_OFFSET_DATA[1][2].y = 0;
    JLSTZ_OFFSET_DATA[1][3].x = -1;
    JLSTZ_OFFSET_DATA[1][3].y = 0;

    JLSTZ_OFFSET_DATA[2][0].x = 0;
    JLSTZ_OFFSET_DATA[2][0].y = 0;
    JLSTZ_OFFSET_DATA[2][1].x = 1;
    JLSTZ_OFFSET_DATA[2][1].y = -1;
    JLSTZ_OFFSET_DATA[2][2].x = 0;
    JLSTZ_OFFSET_DATA[2][2].y = 0;
    JLSTZ_OFFSET_DATA[2][3].x = -1;
    JLSTZ_OFFSET_DATA[2][3].y = 1;

    JLSTZ_OFFSET_DATA[3][0].x = 0;
    JLSTZ_OFFSET_DATA[3][0].y = 0;
    JLSTZ_OFFSET_DATA[3][1].x = 0;
    JLSTZ_OFFSET_DATA[3][1].y = 2;
    JLSTZ_OFFSET_DATA[3][2].x = 0;
    JLSTZ_OFFSET_DATA[3][2].y = 0;
    JLSTZ_OFFSET_DATA[3][3].x = 0;
    JLSTZ_OFFSET_DATA[3][3].y = 2;

    JLSTZ_OFFSET_DATA[4][0].x = 0;
    JLSTZ_OFFSET_DATA[4][0].y = 0;
    JLSTZ_OFFSET_DATA[4][1].x = 1;
    JLSTZ_OFFSET_DATA[4][1].y = 2;
    JLSTZ_OFFSET_DATA[4][2].x = 0;
    JLSTZ_OFFSET_DATA[4][2].y = 0;
    JLSTZ_OFFSET_DATA[4][3].x = -1;
    JLSTZ_OFFSET_DATA[4][3].y = 2;

    I_OFFSET_DATA[0][0].x = 0;
    I_OFFSET_DATA[0][0].y = 0;
    I_OFFSET_DATA[0][1].x = -1;
    I_OFFSET_DATA[0][1].y = 0;
    I_OFFSET_DATA[0][2].x = -1;
    I_OFFSET_DATA[0][2].y = 1;
    I_OFFSET_DATA[0][3].x = 0;
    I_OFFSET_DATA[0][3].y = 1;

    I_OFFSET_DATA[1][0].x = -1;
    I_OFFSET_DATA[1][0].y = 0;
    I_OFFSET_DATA[1][1].x = 0;
    I_OFFSET_DATA[1][1].y = 0;
    I_OFFSET_DATA[1][2].x = 1;
    I_OFFSET_DATA[1][2].y = 1;
    I_OFFSET_DATA[1][3].x = 0;
    I_OFFSET_DATA[1][3].y = 1;

    I_OFFSET_DATA[2][0].x = 2;
    I_OFFSET_DATA[2][0].y = 0;
    I_OFFSET_DATA[2][1].x = 0;
    I_OFFSET_DATA[2][1].y = 0;
    I_OFFSET_DATA[2][2].x = -2;
    I_OFFSET_DATA[2][2].y = 1;
    I_OFFSET_DATA[2][3].x = 0;
    I_OFFSET_DATA[2][3].y = 1;

    I_OFFSET_DATA[3][0].x = -1;
    I_OFFSET_DATA[3][0].y = 0;
    I_OFFSET_DATA[3][1].x = 0;
    I_OFFSET_DATA[3][1].y = 1;
    I_OFFSET_DATA[3][2].x = 1;
    I_OFFSET_DATA[3][2].y = 0;
    I_OFFSET_DATA[3][3].x = 0;
    I_OFFSET_DATA[3][3].y = -1;

    I_OFFSET_DATA[4][0].x = 2;
    I_OFFSET_DATA[4][0].y = 0;
    I_OFFSET_DATA[4][1].x = 0;
    I_OFFSET_DATA[4][1].y = -2;
    I_OFFSET_DATA[4][2].x = -2;
    I_OFFSET_DATA[4][2].y = 0;
    I_OFFSET_DATA[4][3].x = 0;
    I_OFFSET_DATA[4][3].y = 2;

    O_OFFSET_DATA[0][0].x = 0;
    O_OFFSET_DATA[0][0].y = 0;
    O_OFFSET_DATA[0][1].x = 0;
    O_OFFSET_DATA[0][1].y = -1;
    O_OFFSET_DATA[0][2].x = -1;
    O_OFFSET_DATA[0][2].y = -1;
    O_OFFSET_DATA[0][3].x = -1;
    O_OFFSET_DATA[0][3].y = 0;
}