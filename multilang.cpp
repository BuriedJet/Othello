#include <iostream>
#include "elements.h"

using std::string;

void langStrings::setLangStrings(language langFlag)
{
    switch (langFlag)
    {
        case en_us:
            EN_US();
            break;
        case zh_cn:
            ZH_CN();
            break;
        case zh_tw:
            ZH_TW();
            break;
        case zh_wy:
            break;
        case jp:
            break;
        case fr:
            break;
        case es:
            break;
        default:
            break;
    }
}

void langStrings::EN_US()
{
    stitle = "title=JetOthello";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "Othello Main Version ";
    verl2 = "Achilles Version ";
    verl3 = "Copyleft 2015";
    verl4 = "By Jet";

    menu1 = "1.Play with Friends";
    menu2 = "2.Play with Achilles";
    menu3 = "3.Achilles Auto Play";
    menu41 = "4.Turn Off GUI";
    menu42 = "4.Turn On GUI";
    menu5 = "5.Load Game";
    menu6 = "6.Settings";
    menu7 = "7.Instructions";
    menu0 = "0.Exit";

    sglipt = "Input:_\b";

    guion = "GUI Mode On";

    atplbs = "Please Set Mode of Achilles Playing Black";
    atplws = "Please Set Mode of Achilles Playing White";

    ivldipt = "Invalid Input!!!";

    sidesel = "Play Black or White?(B/W):_\b";

    dif[0] = "1.Dumb Mode";
    dif[1] = "2.Easy Mode";
    dif[2] = "3.Normal Mode";
    dif[3] = "4.Hard Mode";
    dif[4] = "5.Call Police Mode";

    isass = "Do You Want Any Assistance When Placing the Stone?(Y/N):_\b";

    seltheme = "Please Select Theme:";
    theme[0] = "0.Default (White on Black)";
    theme[1] = "1.Reverse (Black on White)";
    theme[2] = "2.Borland (Yellow on Blue) ";
    theme[3] = "3.BlueScreen (White on Blue)";
    theme[4] = "4.Geek (Green on Black)";
    theme[5] = "5.Glamorous (Blue on Purple)";
    theme[6] = "6.Pinky (Yellow on Pink)";
    theme[7] = "7.Yima (White on Red)";
    theme[8] = "8.DiDiaoYiMa (Red on Black)";
    theme[9] = "9.Dragon (Yellow on Dark Red)";
    rdmtheme = "Input JET to Randomize the Theme.";
    triipt = "Input:___\b\b\b";

    sts[0] = "1.Select Console Theme";
    sts[1] = "2.Select Language";
    sts[2] = "3.Assistance Setting";
    sts[3] = "0.Back to Main Menu";

    themenspt = "Sorry, Theme Changing Only Support in Windows...";

    rnd = "          Round ";
    rnd1.clear();
    blk = "Black";
    wht = "White";
    trn = "'s Turn";
    aps = "Achilles Placed a Stone at ";
    aps1.clear();
    tmcsm1.clear();
    tmcsm = " Seconds Consumed.";

    gmrcd = "Game Record:";
    pass = "PASS";

    savefl = "    Unable to Save, Game Will Now Resume!";
    savedmg = "Saved File Damaged!";
    savess = "         Game Successfully Saved!";
    gotomainspc = "       ";
    loadfl = "Unable to Open Saved File!";

    gotomain = "Press Any Key to Main Menu...";

    ytrn1 = "            Your(��) Turn:__\b\b";
    ytrn2 = "            Your(��) Turn:__\b\b";

    btrn = "           Black(��) Turn:__\b\b";
    wtrn = "           White(��) Turn:__\b\b";

    nposm = "      No Possible Move, Enter to Pass!";
    aipass = "      Achilles Passed, Enter to Your Turn!";

    ip = "       Invalid Position! Your input is ";

    aithink = "            Achilles Thinking ...";

    dftai = "    You Defeated Achilles! Congratulations!";
    toosimple = "           Too Young Too Simple!";
    tieai = "Tie!";
    tie = "Tie!";
    win = "Win!";
}

void langStrings::ZH_CN()
{
    stitle = "title=��С˧�ĺڰ���";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "�ڰ���������汾 ";
    verl2 = "Achilles�汾 ";
    verl3 = "Copyleft 2015";
    verl4 = "By ��С˧";

    menu1 = "1.������һ�������PvP��";
    menu2 = "2.��Achilles�����PvAI��";
    menu3 = "3.��Achilles�Լ������AIvAI��";
    menu41 = "4.�ر�ͼ�ν���";
    menu42 = "4.��ͼ�ν���";
    menu5 = "5.������Ϸ";
    menu6 = "6.��Ϸ����";
    menu7 = "7.����";
    menu0 = "0.�˳���Ϸ";

    sglipt = "������:_\b";

    guion = "ͼ�ν����Ѵ�";

    atplbs = "��ѡ��ڷ�Achillesģʽ";
    atplws = "��ѡ��׷�Achillesģʽ";

    ivldipt = "���벻��ȷ!!!";

    sidesel = "��Ҫִ�ڻ���ִ�ף�(B/W):_\b";

    dif[0] = "1.������ģʽ";
    dif[1] = "2.��ģʽ";
    dif[2] = "3.����ģʽ";
    dif[3] = "4.����ģʽ";
    dif[4] = "5.����ģʽ";

    isass = "����ʱ��Ҫ��ʾ����λ����(Y/N):_\b";

    seltheme = "��ѡ�����⣺";
    theme[0] = "0.Ĭ������ (��/��)";
    theme[1] = "1.��ɫ (��/��)";
    theme[2] = "2.�������� (ǳ��/��) ";
    theme[3] = "3.���� (��/��)";
    theme[4] = "4.���� (��/��)";
    theme[5] = "5.����Ī��˿ (��/��)";
    theme[6] = "6.���� (��/��)";
    theme[7] = "7.���� (��/��)";
    theme[8] = "8.�͵����� (��/��)";
    theme[9] = "9.�� (��/��)���Ƽ���";
    rdmtheme = "���� JET �Ի�����������.";
    triipt = "����:___\b\b\b";

    sts[0] = "1.ѡ������������";
    sts[1] = "2.ѡ������";
    sts[2] = "3.����ģʽ����";
    sts[3] = "0.�������˵�";

    themenspt = "�ܱ�Ǹ���������⹦��ֻ����Windows��ʹ��...";

    rnd = "             ��";
    rnd1 = "��";
    blk = "�ڷ�";
    wht = "�׷�";
    trn = "�غ�";
    aps = "   Achilles�� ";
    aps1 = " ������";
    tmcsm1 = "    ��ʱ";
    tmcsm = " ��.";

    gmrcd = "��Ϸ��¼:";
    pass = "PASS";

    savefl = "         ����ʧ�ܣ���Ϸ��������";
    savedmg = "�浵�ļ���";
    savess = "               ��Ϸ�ɹ�����";
    gotomainspc = "           ";
    loadfl = "�޷��򿪴浵�ļ���";

    gotomain = "��������ص����˵�...";

    ytrn1 = "             ��(��) �Ļغ�:__\b\b";
    ytrn2 = "             ��(��) �Ļغ�:__\b\b";

    btrn = "            ����(��) �Ļغ�:__\b\b";
    wtrn = "            ����(��) �Ļغ�:__\b\b";

    nposm = "        �����ӿ��£����س��������غ�";
    aipass = "  Achilles �����˻غ�, ���س���������Ļغ�";

    ip = "           ��λ�ò������ӣ���������� ";

    aithink = "           Achilles ����˼�� ...";

    dftai = "            ������ Achilles! NB!";
    toosimple = "        Too Young Too Simple!";
    tieai = "                    ƽ�֣�";
    tie = "ƽ��!";
    win = "��ʤ!";

}


void langStrings::ZH_TW()
{
    stitle = "title=���󎛵ĺڰ���";
    for (int i = 0; i < stitle.length(); i++)
        title[i] = stitle[i];
    title[stitle.length()] = '\0';

    verl1 = "�ڰ�������ʽ�汾 ";
    verl2 = "Achilles�汾 ";
    verl3 = "Copyleft 2015";
    verl4 = "By ����";

    menu1 = "1.������һ���棨PvP��";
    menu2 = "2.��Achilles�棨PvAI��";
    menu3 = "3.��Achilles�Լ��棨AIvAI��";
    menu41 = "4.�P�]�D�ν���";
    menu42 = "4.���_�D�ν���";
    menu5 = "5.�d���[��";
    menu6 = "6.�[���O��";
    menu7 = "7.����";
    menu0 = "0.�˳��[��";

    sglipt = "Ոݔ��:_\b";

    guion = "�D�ν����Ѵ��_";

    atplbs = "Ո�x��ڷ�Achillesģʽ";
    atplws = "Ո�x��׷�Achillesģʽ";

    ivldipt = "ݔ�벻���_!!!";

    sidesel = "����̺�߀�ǈ̰ף�(B/W):_\b";

    dif[0] = "1.�һƽģʽ";
    dif[1] = "2.����ģʽ";
    dif[2] = "3.����ģʽ";
    dif[3] = "4.���yģʽ";
    dif[4] = "5.��ģʽ";

    isass = "����r��Ҫ��ʾ����λ�Æ᣿(Y/N):_\b";

    seltheme = "Ո�x�����}��";
    theme[0] = "0.�A�O���} (��/��)";
    theme[1] = "1.��ɫ (��/��)";
    theme[2] = "2.�����m�� (�\�S/�{) ";
    theme[3] = "3.�{�� (��/�{)";
    theme[4] = "4.�O�� (�G/��)";
    theme[5] = "5.����Ī�}�z (�{/��)";
    theme[6] = "6.���� (�S/��)";
    theme[7] = "7.�̋� (��/�t)";
    theme[8] = "8.���{�̋� (�t/��)";
    theme[9] = "9.�� (�S/�t)�����]��";
    rdmtheme = "�I�� JET �ԫ@���S�C�����}.";
    triipt = "ݔ��:___\b\b\b";

    sts[0] = "1.�x�����������}";
    sts[1] = "2.�x���Z��";
    sts[2] = "3.�o��ģʽ�_�P";
    sts[3] = "0.�������ˆ�";

    themenspt = "�ܱ�Ǹ�����Q���}����ֻ����Windows��ʹ��...";

    rnd = "             ��";
    rnd1 = "݆";
    blk = "�ڷ�";
    wht = "�׷�";
    trn = "�غ�";
    aps = "   Achilles�� ";
    aps1 = " ̎����";
    tmcsm1 = "    �ĕr";
    tmcsm = " ��.";

    gmrcd = "�[��ӛ�:";
    pass = "PASS";

    savefl = "         ����ʧ�����[���^�m��";
    savedmg = "��n�ļ��p��";
    savess = "               �[��ɹ�����";
    gotomainspc = "           ";
    loadfl = "�o�����_��n�ļ���";

    gotomain = "�������I�ص����ˆ�...";

    ytrn1 = "             ��(��) �Ļغ�:__\b\b";
    ytrn2 = "             ��(��) �Ļغ�:__\b\b";

    btrn = "            ����(��) �Ļغ�:__\b\b";
    wtrn = "            ����(��) �Ļغ�:__\b\b";

    nposm = "        ���o�ӿ��£�����܇�����^�غ�";
    aipass = "  Achilles ���^�˻غ�, ����܇���M����Ļغ�";

    ip = "           ԓλ�ò������ӣ���ݔ����� ";

    aithink = "           Achilles ����˼�� ...";

    dftai = "            ����� Achilles! NB!";
    toosimple = "        Too Young Too Simple!";
    tieai = "                    ƽ�֣�";
    tie = "ƽ��!";
    win = "�@��!";
}

void langStrings::printVersion()
{
    cout << verl1 << MAIN_VERSION << endl;
    cout << verl2 << ACHILLES_VERSION << endll;
    cout << verl3 << endl;
    cout << verl4 << endll;
}

void langStrings::printMenu()
{
    CLS;

    if (PRINT_VERSION)
        printVersion();

    if (Game::UIFlag)
        cout << guion << endll;
    else
        cout << endl;

    cout << menu1 << endl;
    cout << menu2 << endl;
    cout << menu3 << endl;
    if (Game::UIFlag)
        cout << menu41 << endl;
    else
        cout << menu42 << endl;
    cout << menu5 << endl;
    cout << menu6 << endl;
    cout << menu7 << endl;
    cout << menu0 << endll;
    cout << sglipt;
}

void langStrings::help()
{
    CLS;
    cout << "***************************************************" << endll;
    cout << "ON THE BOARD OF COMMAND LINE MODE:" << endll;
    cout << "'��' STANDS FOR BLACK  '��' STANDS FOR WHITE" << endl;
    cout << "'��' MEANS THE CELL IS VALID TO PLACE YOUR STONE" << endl;
    cout << "'  ' MEANS THE CELL IS CURRENT EMPTY AND INVALID" << endll;
    cout << "7A,A7,7a,a7 ARE ALL RECOGNIZABLE INPUTS" << endll;
    cout << "***************************************************" << endll;
    cout << "YOU CAN INPUT THESE COMMAND DURING THE GAME" << endl;
    cout << "INSTEAD OF INPUTTING THE COORDINATE:" << endll;
    cout << "1.EXIT: ABORT THE GAME AND EXIT." << endll;
    cout << "2.MENU: ABORT THE GAME AND GO BACK TO THE MAIN MENU." << endll;
    cout << "3.SAVE: SAVE THE GAME AND GO BACK TO THE MAIN MENU." << endll;
    cout << "4.UNDO: UNDO YOUR (AND ACHILLES') LAST MOVE." << endll;
    cout << "***************************************************" << endll;
    cout << endll;
    PAUSE;
}

