#include "testutils/FuseReadTest.h"

#include "fspp/impl/FuseErrnoException.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::WithParamInterface;
using ::testing::Values;
using ::testing::Eq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::Throw;

using namespace fspp;

class FuseReadFileDescriptorTest: public FuseReadTest, public WithParamInterface<int> {
};
INSTANTIATE_TEST_CASE_P(FuseReadFileDescriptorTest, FuseReadFileDescriptorTest, Values(0,1,10,1000,1024*1024*1024));


TEST_P(FuseReadFileDescriptorTest, FileDescriptorIsCorrect) {
  ReturnIsFileOnLstat(FILENAME);
  OnOpenReturnFileDescriptor(FILENAME, GetParam());
  EXPECT_CALL(fsimpl, read(Eq(GetParam()), _, _, _))
    .Times(1).WillOnce(ReturnSuccessfulRead);

  char buf[1];
  ReadFile(FILENAME, buf, 0, 0);
}
