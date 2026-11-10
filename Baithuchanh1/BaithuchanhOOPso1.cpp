#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class phuong_tien {
private:
    int ma_xe; string loai_xe; int gio_vao;
    int tg_do;
    double phi_do;
    bool dang_chiem;
public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;

    void gan_trang_thai(bool trang_thai);

    static string chuan_hoa_loai(string loai);
    static bool loai_hop_le(string loai);

    void cap_nhat_phi();
    void hien_thi() const;
};
phuong_tien::phuong_tien() {
    ma_xe = 0; loai_xe = ""; gio_vao = 0; tg_do = 1; phi_do = 0; dang_chiem = false;
}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
    ma_xe = ma; loai_xe = ""; gio_vao = 0; tg_do = 1; phi_do = 0; dang_chiem = false;

    string loai_chuan = chuan_hoa_loai(loai);
    
    if (loai_chuan != "")
        loai_xe = loai_chuan;
    if (gio >= 0 && gio <= 23)
        gio_vao = gio;
    if (tg >= 1 && tg <= 23)
        tg_do = tg;

    cap_nhat_phi();
}
int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
double phuong_tien::tinh_phi() const { return phi_do; }
void phuong_tien::gan_trang_thai(bool trang_thai) { dang_chiem = trang_thai; }
string phuong_tien::chuan_hoa_loai(string loai) {
    for (int i = 0; i < (int)loai.length(); i++)
        loai[i] = tolower((unsigned char)loai[i]);
    if (loai == "car")
        return "Car";
    else if (loai == "motorcycle")
        return "Motorcycle";
    else if (loai == "bicycle")
        return "Bicycle";
    return "";
}
bool phuong_tien::loai_hop_le(string loai) { return chuan_hoa_loai(loai) != ""; }

void phuong_tien::cap_nhat_phi() {
    double phi_gio = 0;
    if (!loai_hop_le(loai_xe)) {
        phi_do = 0;
        return;
    }
    if (loai_xe == "Car")
        phi_gio = 6;
    else if (loai_xe == "Motorcycle")
        phi_gio = 4;
    else
        phi_gio = 2;
    if ((gio_vao >= 6 && gio_vao < 10) || (gio_vao >= 15 && gio_vao < 19)) {
        if (tg_do <= 2)
            phi_do = phi_gio*tg_do*1.3;
        else
            phi_do = phi_gio*2*1.3 + phi_gio*(tg_do - 2)*0.9;
    }
    else {
        if (tg_do <= 2)
            phi_do = phi_gio*tg_do * 0.95;
        else
            phi_do = phi_gio*2*0.95 + phi_gio*(tg_do - 2)*0.9;
    }
}
void phuong_tien::hien_thi() const {
    cout << "Ma xe: " << ma_xe << endl;
    cout << "Loai xe: " << loai_xe << endl;
    cout << "Gio vao: " << gio_vao << endl;
    cout << "Thoi gian do: " << tg_do << " gio" << endl;
    cout << "Phi do xe: " << fixed << setprecision(2) << phi_do << endl;
    cout << "Trang thai: "
         << (dang_chiem ? "Dang chiem cho" : "Khong chiem cho") << endl;
}
class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;

    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_suc_chua() const;
    int lay_so_luong() const;

    bool con_cho() const;
    bool dang_co_xe() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;

    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};
bai_xe::bai_xe() { ma_bai = 0; kich_thuoc = 'S'; co1 = false; co2 = false; co3 = false; }
bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kt = toupper((unsigned char)kt);
    if (kt == 'S' || kt == 'M' || kt == 'L')
        kich_thuoc = kt;
    else
        kich_thuoc = 'S';
    co1 = false;
    co2 = false;
    co3 = false;
}
int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
int bai_xe::lay_suc_chua() const {
    if (kich_thuoc == 'S')
        return 1;
    else if (kich_thuoc == 'M')
        return 2;
    else
        return 3;
}
int bai_xe::lay_so_luong() const {
    int dem = 0;
    if (co1) dem++;
    if (co2) dem++;
    if (co3) dem++;
    return dem;
}
bool bai_xe::con_cho() const { return lay_so_luong() < lay_suc_chua(); }

// Kiem tra bai xe co dang chua phuong tien hay khong.
bool bai_xe::dang_co_xe() const {
    return lay_so_luong() > 0;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe)
        return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe)
        return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe)
        return true;
    return false;
}
bool bai_xe::them(phuong_tien v) {
    if (!con_cho())
        return false;
    if (chua(v.lay_ma_xe()))
        return false;
    v.gan_trang_thai(true);
    if (!co1) {
        pt1 = v;
        co1 = true;
        return true;
    }
    if (lay_suc_chua() >= 2 && !co2) {
        pt2 = v;
        co2 = true;
        return true;
    }
    if (lay_suc_chua() >= 3 && !co3) {
        pt3 = v;
        co3 = true;
        return true;
    }
    return false;
}
bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        pt1 = phuong_tien();
        co1 = false;
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        pt2 = phuong_tien();
        co2 = false;
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        pt3 = phuong_tien();
        co3 = false;
        return true;
    }
    return false;
}
void bai_xe::hien_thi() const {
    cout << "\n========== THONG TIN BAI XE ==========\n";
    cout << "Ma bai: " << ma_bai << endl;
    cout << "Kich thuoc: " << kich_thuoc << endl;
    cout << "Suc chua: " << lay_suc_chua() << " xe" << endl;
    cout << "So xe hien tai: " << lay_so_luong() << endl;

    if (co1) {
        cout << "\n--- Xe o cho 1 ---\n";
        pt1.hien_thi();
    }
    if (co2) {
        cout << "\n--- Xe o cho 2 ---\n";
        pt2.hien_thi();
    }
    if (co3) {
        cout << "\n--- Xe o cho 3 ---\n";
        pt3.hien_thi();
    }
    if (lay_so_luong() == 0)
        cout << "Bai xe dang trong.\n";

    cout << "======================================\n";
}
bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    loai = phuong_tien::chuan_hoa_loai(loai);

    if (loai == "")
        return false;
    if (co1 && pt1.lay_loai_xe() == loai) {
        dem++;
        tong += pt1.tinh_phi();
    }
    if (co2 && pt2.lay_loai_xe() == loai) {
        dem++;
        tong += pt2.tinh_phi();
    }
    if (co3 && pt3.lay_loai_xe() == loai) {
        dem++;
        tong += pt3.tinh_phi();
    }
    return true;
}
class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

    bool tonTaiBai(int maBai) const;
    bai_xe* timBai(int maBai);
    bool tonTaiMaXe(int maXe) const;

    void taoBaiXe();
    void themXeVaoBai();
    void xoaBaiXe();
    void layXeRa();
    void hienThiTatCaBai();
    void hienThiXeTrongBai();
    void thongKeTheoLoai();
    void tinhPhiTrungBinh();

public:
    SystemInterface();
    void runMenu();
};
SystemInterface::SystemInterface() { co1 = false; co2 = false; co3 = false; }
bool SystemInterface::tonTaiBai(int maBai) const {
    if (co1 && bai1.lay_ma() == maBai)
        return true;
    if (co2 && bai2.lay_ma() == maBai)
        return true;
    if (co3 && bai3.lay_ma() == maBai)
        return true;
    return false;
}
bai_xe* SystemInterface::timBai(int maBai) {
    if (co1 && bai1.lay_ma() == maBai)
        return &bai1;
    if (co2 && bai2.lay_ma() == maBai)
        return &bai2;
    if (co3 && bai3.lay_ma() == maBai)
        return &bai3;
    return NULL;
}
bool SystemInterface::tonTaiMaXe(int maXe) const {
    if (co1 && bai1.chua(maXe))
        return true;
    if (co2 && bai2.chua(maXe))
        return true;
    if (co3 && bai3.chua(maXe))
        return true;
    return false;
}
void SystemInterface::taoBaiXe() {
    if (co1 && co2 && co3) {
        cout << "He thong da du 3 bai xe!\n";
        return;
    }

    int maBai;
    char kichThuoc;

    cout << "Nhap ma bai xe: ";
    cin >> maBai;

    if (maBai <= 0) {
        cout << "Ma bai xe phai la so duong!\n";
        return;
    }

    if (tonTaiBai(maBai)) {
        cout << "Ma bai xe da ton tai!\n";
        return;
    }

    cout << "Nhap kich thuoc (S/M/L): ";
    cin >> kichThuoc;

    kichThuoc = toupper((unsigned char)kichThuoc);

    if (kichThuoc != 'S' &&
        kichThuoc != 'M' &&
        kichThuoc != 'L') {
        cout << "Kich thuoc khong hop le!\n";
        return;
    }

    if (!co1) {
        bai1 = bai_xe(maBai, kichThuoc);
        co1 = true;
    }
    else if (!co2) {
        bai2 = bai_xe(maBai, kichThuoc);
        co2 = true;
    }
    else {
        bai3 = bai_xe(maBai, kichThuoc);
        co3 = true;
    }

    cout << "Tao bai xe thanh cong!\n";
}
void SystemInterface::themXeVaoBai() {
    int maBai, maXe, gioVao, thoiGian;
    string loaiXe;

    cout << "Nhap ma bai xe: ";
    cin >> maBai;

    if (!tonTaiBai(maBai)) {
        cout << "Khong tim thay bai xe!\n";
        return;
    }

    bai_xe* bai = timBai(maBai);

    if (bai == NULL || !bai->con_cho()) {
        cout << "Bai xe da day!\n";
        return;
    }

    cout << "Nhap ma xe: ";
    cin >> maXe;

    if (maXe <= 0) {
        cout << "Ma xe phai la so duong!\n";
        return;
    }

    if (tonTaiMaXe(maXe)) {
        cout << "Ma xe da ton tai trong he thong!\n";
        return;
    }

    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loaiXe;

    if (!phuong_tien::loai_hop_le(loaiXe)) {
        cout << "Loai xe khong hop le!\n";
        return;
    }

    cout << "Nhap gio vao (0-23): ";
    cin >> gioVao;

    if (gioVao < 0 || gioVao > 23) {
        cout << "Gio vao khong hop le!\n";
        return;
    }

    cout << "Nhap thoi gian do (1-23 gio): ";
    cin >> thoiGian;

    if (thoiGian < 1 || thoiGian > 23) {
        cout << "Thoi gian do khong hop le!\n";
        return;
    }

    phuong_tien xe(maXe, loaiXe, gioVao, thoiGian);

    if (bai->them(xe))
        cout << "Them xe thanh cong!\n";
    else
        cout << "Khong the them xe!\n";
}
void SystemInterface::xoaBaiXe() {
    int maBai;

    cout << "Nhap ma bai xe can xoa: ";
    cin >> maBai;

    if (co1 && bai1.lay_ma() == maBai) {
        if (bai1.dang_co_xe()) {
            cout << "Khong the xoa bai xe vi van con xe! Hay lay het xe ra truoc.\n";
            return;
        }
        bai1 = bai_xe();
        co1 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    if (co2 && bai2.lay_ma() == maBai) {
        if (bai2.dang_co_xe()) {
            cout << "Khong the xoa bai xe vi van con xe! Hay lay het xe ra truoc.\n";
            return;
        }
        bai2 = bai_xe();
        co2 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    if (co3 && bai3.lay_ma() == maBai) {
        if (bai3.dang_co_xe()) {
            cout << "Khong the xoa bai xe vi van con xe! Hay lay het xe ra truoc.\n";
            return;
        }
        bai3 = bai_xe();
        co3 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::layXeRa() {
    int maBai, maXe;

    cout << "Nhap ma bai xe: ";
    cin >> maBai;

    if (!tonTaiBai(maBai)) {
        cout << "Khong tim thay bai xe!\n";
        return;
    }

    bai_xe* bai = timBai(maBai);

    cout << "Nhap ma xe can lay ra: ";
    cin >> maXe;

    if (bai != NULL && bai->xoa(maXe))
        cout << "Lay xe ra thanh cong!\n";
    else
        cout << "Khong tim thay xe trong bai!\n";
}
void SystemInterface::hienThiTatCaBai() {
    bool coBai = false;

    if (co1) {
        bai1.hien_thi();
        coBai = true;
    }

    if (co2) {
        bai2.hien_thi();
        coBai = true;
    }

    if (co3) {
        bai3.hien_thi();
        coBai = true;
    }

    if (!coBai)
        cout << "He thong chua co bai xe nao!\n";
}
void SystemInterface::hienThiXeTrongBai() {
    int maBai;

    cout << "Nhap ma bai xe can xem: ";
    cin >> maBai;

    if (co1 && bai1.lay_ma() == maBai) {
        bai1.hien_thi();
        return;
    }

    if (co2 && bai2.lay_ma() == maBai) {
        bai2.hien_thi();
        return;
    }

    if (co3 && bai3.lay_ma() == maBai) {
        bai3.hien_thi();
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}
void SystemInterface::thongKeTheoLoai() {
    string loaiXe;
    int dem = 0;
    double tongPhi = 0;

    cout << "Nhap loai xe can thong ke (Car/Motorcycle/Bicycle): ";
    cin >> loaiXe;

    loaiXe = phuong_tien::chuan_hoa_loai(loaiXe);

    if (loaiXe == "") {
        cout << "Loai xe khong hop le!\n";
        return;
    }

    if (co1)
        bai1.co_loai(loaiXe, dem, tongPhi);

    if (co2)
        bai2.co_loai(loaiXe, dem, tongPhi);

    if (co3)
        bai3.co_loai(loaiXe, dem, tongPhi);

    cout << "\nLoai xe: " << loaiXe << endl;
    cout << "So luong xe: " << dem << endl;
    cout << "Tong phi do xe: " << fixed << setprecision(2)
         << tongPhi << endl;
}
void SystemInterface::tinhPhiTrungBinh() {
    string loaiXe;
    int dem = 0;
    double tongPhi = 0;

    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loaiXe;

    loaiXe = phuong_tien::chuan_hoa_loai(loaiXe);

    if (loaiXe == "") {
        cout << "Loai xe khong hop le!\n";
        return;
    }

    if (co1)
        bai1.co_loai(loaiXe, dem, tongPhi);

    if (co2)
        bai2.co_loai(loaiXe, dem, tongPhi);

    if (co3)
        bai3.co_loai(loaiXe, dem, tongPhi);

    if (dem == 0) {
        cout << "Khong co xe thuoc loai nay!\n";
        return;
    }

    cout << "Phi do xe trung binh cua " << loaiXe << ": "
         << fixed << setprecision(2)
         << tongPhi / dem << endl;
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n========== QUAN LY BAI DO XE ==========\n";
        cout << "1. Tao bai xe\n";
        cout << "2. Them xe vao bai\n";
        cout << "3. Xoa bai xe\n";
        cout << "4. Lay xe ra khoi bai\n";
        cout << "5. Hien thi tat ca bai xe\n";
        cout << "6. Hien thi xe trong mot bai\n";
        cout << "7. Thong ke xe theo loai\n";
        cout << "8. Tinh phi do xe trung binh theo loai\n";
        cout << "9. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;
        switch (chon){
        case 1:
            taoBaiXe(); break;
        case 2:
            themXeVaoBai(); break;
        case 3:
            xoaBaiXe(); break;
        case 4:
            layXeRa(); break;
        case 5:
            hienThiTatCaBai(); break;
        case 6:
            hienThiXeTrongBai(); break;
        case 7:
            thongKeTheoLoai(); break;
        case 8:
            tinhPhiTrungBinh(); break;
        case 9:
            cout << "Da thoat chuong trinh!\n"; break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 9);
}
int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}
