#include "ast/built_ins/Pose2dExprAST.h"
#include "built_ins/BuiltInTypes.h"

llvm::Value *Pose2dExprAST::codegen() {
    auto ptr_x = x->codegen();
    auto ptr_y = y->codegen();
    auto ptr_theta = theta->codegen();

    llvm::AllocaInst* instance = (llvm::AllocaInst*) destination->codegen();

    llvm::APInt zero(32, 0);
    llvm::APInt one(32, 1);
    llvm::APInt two(32, 2);

    std::vector<llvm::Value *> x_pos {
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), zero),
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), zero)
    };
    std::vector<llvm::Value *> y_pos {
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), zero),
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), one)
    };
    std::vector<llvm::Value *> theta_pos {
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), zero),
        llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(TheContext), two)
    };

    llvm::Value* gep_x = Builder.CreateGEP(
        instance,
        x_pos, // index 0, 0: Pose2.x
        "gep_pose2_x"
    );
    Builder.CreateStore(ptr_x, gep_x);

    llvm::Value* gep_y = Builder.CreateInBoundsGEP(
        instance,
        y_pos, // index 0, 0: Pose2.y
        "gep_pose2_y"
    );
    Builder.CreateStore(ptr_y, gep_y);

    llvm::Value* gep_theta = Builder.CreateInBoundsGEP(
        instance,
        theta_pos, // index 0, 0: Pose2.theta
        "gep_pose2_theta"
    );
    Builder.CreateStore(ptr_theta, gep_theta);
    return instance;
}
