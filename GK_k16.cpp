#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct THONG_TIN_THUOC{
    char ma_thuoc[12];//mã thuốc
    char ten_thuoc[60];//tên thuốc
    char loai_thuoc[60]; 
    int so_luong_nhap;// số lượng
    int so_luong_ban;
};

//Khai bao cua truc node
struct NODE{
    THONG_TIN_THUOC data;
    struct NODE *pNext;
};

//Khoi tao list
struct LIST{
    NODE *pHead;
    NODE *pTail;
};

void List(struct LIST *l);
void InsertNode(struct LIST *l, THONG_TIN_THUOC thuoc);
void NhapDanhMucThuoc(struct LIST *l);
void XuatDanhMucBanHet(struct LIST l);
void NhapThemDanhMucThuoc(struct LIST *l);
void SapXepTangDanTheoMaThuoc(struct LIST *l);
void FreeList(struct LIST *l);


//Khai bao cau truc list
void List(struct LIST *l){
    l->pHead = NULL;
    l->pTail = NULL;
}

//Khoi tao node
void InsertNode(struct LIST *l, THONG_TIN_THUOC thuoc){
    struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
    newNode->data = thuoc;
    newNode->pNext = NULL;

    if(l->pHead == NULL){
        l->pHead = newNode;
        l->pTail = newNode;
    } else {
        // Nếu danh sách không rỗng, nút mới được thêm vào sau nút cuối cùng
        l->pTail->pNext = newNode;
        // (nghĩa là nút cuối cùng hiện tại sẽ trỏ tới nút mới và nút mới trở thành nút cuối)
        l->pTail = newNode;
    }
}


void NhapDanhMucThuoc(struct LIST *l){
    THONG_TIN_THUOC thuoc;
    printf("Nhap moi danh muc thuoc (Nhap ma thuoc la -1 de dung): ");
    while(1){
        printf("Nhap ma thuoc: ");
        scanf("%s", thuoc.ma_thuoc);
        if(strcmp(thuoc.ma_thuoc, "-1") == 0){
            break;
        }

        printf("Nhap ten thuoc: ");
        scanf("%s", thuoc.ten_thuoc);

        printf("Nhap loai thuoc: ");
        scanf("%s", thuoc.loai_thuoc);

        printf("Nhap so luong nhap: ");
        scanf("%d", thuoc.so_luong_nhap);

        do{
            printf("Nhap so luong ban (nho hon so luong nhap): ");
            scanf("%d", thuoc.so_luong_ban);
        } while(thuoc.so_luong_ban >= thuoc.so_luong_nhap);
        //Hàm InsertNode này giúp thêm thông tin của một loại thuốc vào cuối danh sách liên kết,
        //và nếu danh sách liên kết rỗng, nó tạo một nút mới và làm cho head và tail trỏ đến nút mới đó.
        InsertNode(l,thuoc);
    }
}


void XuatDanhMucBanHet(struct LIST l){
    //Khai báo một con trỏ 'current' trỏ đến đầu danh sách liên kết 'list'
    struct NODE *current = l.pHead;
    printf("\nDanh muc da ban het:\n");
    // Duyệt qua từng nút trong danh sách liên kết
    while(current != NULL){
        if(current->data.so_luong_nhap == current->data.so_luong_ban){
            printf("Ma thuoc: %s\n", current->data.ma_thuoc);
            printf("Ten thuoc: %s\n", current->data.ten_thuoc);
            printf("Loai thuoc: %s\n", current->data.loai_thuoc);
            printf("So luong nhap: %d\n", current->data.so_luong_nhap);
            printf("So luong ban: %d\n", current->data.so_luong_ban);
            printf("---------------\n");
        }
        //di chuyển current đến node tiếp theo
        current = current->pNext;
    }
}


void NhapThemDanhMucThuoc(struct LIST *l){
    char ma_thuoc[12];
    int so_luong_them;
    printf("Nhap them danh muc thuoc(Nhap ma thuoc la -1 de ket thuc: \n)");
    while(1){
        printf("Nhap ma thuoc: ");
        scanf("%s", ma_thuoc);
        if(strcmp(ma_thuoc, "-1") == 0){
            break;
        }
        struct NODE *current = l->pHead;
        //Duyệt qua từng node trong dslk
        while(current != NULL){
            // Kiểm tra xem mã thuốc đã tồn tại trong danh sách hay chưa
            if(strcmp(current->data.ma_thuoc, ma_thuoc) == 0){
               // Nếu mã thuốc đã tồn tại, yêu cầu người dùng nhập thêm số lượng
                printf("Nhap them so luong thuoc: ");
                scanf("%d", &so_luong_them);

                // Cập nhật số lượng nhập của thuốc đã tồn tại
                current->data.so_luong_nhap += so_luong_them;
                break;
            }
            //Di chuyển con trỏ đến node tiếp theo trong ds
            current = current->pNext;
        }
        //Nếu mã thuốc chưa tồn tại trong ds
        if(current == NULL){
            // Hiển thị thông báo và yêu cầu nhập thông tin mới cho thuốc
            printf("Danh muc thuoc chua co, moi nhap moi.\n");

            //Khởi tạo biến thuốc để lưu thông tin mới
            THONG_TIN_THUOC thuoc;
            
            //Sao chép mã thuốc từ biến ma_thuoc vao thuoc.ma_thuoc
            strcpy(thuoc.ma_thuoc, ma_thuoc);

            //Nhập lại ttin cho thuốc
            printf("Nhap ten thuoc: ");
            scanf("%s", thuoc.ten_thuoc);
            printf("Nhap loai thuoc: ");
            scanf("%s", thuoc.loai_thuoc);
            printf("Nhap so luong nhap: ");
            scanf("%d", &thuoc.so_luong_nhap);

            //Nhap so lượng bán, đảm bảo không lớn hơn số lượng nhập
            do{
                printf("Nhap so luong ban(nho hon so luong nhap): ");
                scanf("%d", &thuoc.so_luong_ban);
            } while(thuoc.so_luong_ban >= thuoc.so_luong_nhap);

            // Gọi hàm insertNode để thêm thông tin thuốc mới vào danh sách
            InsertNode(l, thuoc);
        }
    }
}

void Swap(struct NODE *a, struct NODE *b){
    THONG_TIN_THUOC temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void SapXepTangDanTheoMaThuoc(struct LIST *l){
    // Khai báo hai con trỏ 'current' và 'index' để duyệt danh sách
    struct NODE *current, *index;

    // Sắp xếp danh sách bằng thuật toán nổi bọt
    for(current = l->pHead; current != NULL; current = current->pNext){
        for(index = current->pNext; index != NULL; index = index->pNext){
            // So sánh mã thuốc của hai nút để xác định thứ tự sắp xếp
            if(strcmp(current->data.ma_thuoc, index->data.ma_thuoc) == 0){
                // Nếu mã thuốc của nút hiện tại lớn hơn mã thuốc của nút tiếp theo,
                // hoán đổi thông tin giữa hai nút để đảm bảo sắp xếp tăng dần
                Swap(current,index);
            }
        }
    }

    //In ra ds sau khi duoc sap xep
    printf("Danh muc thuoc sau khi sap xep tang dan theo ma thuoc:\n");
    struct NODE *temp = l->pHead;

    printf("Ma thuoc: %s\n", temp->data.ma_thuoc);
    printf("Ten thuoc: %s\n", temp->data.ten_thuoc);
    printf("Loai thuoc: %s\n", temp->data.loai_thuoc);
    printf("So luong nhap: %d\n", temp->data.so_luong_nhap);
    printf("So luong ban: %d\n", temp->data.so_luong_ban);
    printf("---------------\n");

    //Di chuyển đến node tiếp theo trong danh sach
    temp = temp->pNext;
}

void FreeList(struct LIST *l) {
    struct NODE *current = l->pHead;
    struct NODE *next;

    while (current != NULL) {
        next = current->pNext;
        free(current);
        current = next;
    }

    l->pHead = NULL;
    l->pTail = NULL;
}


int main(){
    struct LIST danh_sach_thuoc;
    List(&danh_sach_thuoc);

    int luachon;
    do{
        printf("\nMENU\n");
        printf("1. Nhap moi danh sach thuoc. \n");
        printf("2. Xuat đanh muc thuoc da ban het. \n");
        printf("3. Nhap them danh muc thuoc. \n");
        printf("4. Sap xep thuoc tang dan theo ma thuoc. \n");
        printf("5. Thoat. \n\n");

        printf("Nhap lua chon cua ban: \n");
        scanf("%d",&luachon);

        switch(luachon){
            case 1:
                NhapDanhMucThuoc(&danh_sach_thuoc);
                break;
            case 2:
                XuatDanhMucBanHet(danh_sach_thuoc);
                break;
            case 3:
                NhapThemDanhMucThuoc(&danh_sach_thuoc);
                break;
            case 4:
                SapXepTangDanTheoMaThuoc(&danh_sach_thuoc);
                break;
            case 5:
                FreeList(&danh_sach_thuoc);
                printf("Ket thuc chuong trinh!!!\n");
                break;
            default:
                printf("Lua chon khong hop le!. Chon lai: \n");
        }
    } while(luachon != 5);
    return 0;
}