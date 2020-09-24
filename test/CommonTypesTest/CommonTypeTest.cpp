#include "gtest/gtest.h"
#include "lib/CommonTypes.h"
#include "lib/Texture.h"


// Move to a Texture test
TEST(Common, flipImage) {
    unsigned char picture [] = {
        (unsigned char)255, (unsigned char)0, (unsigned char)0,(unsigned char)255,          (unsigned char)0, (unsigned char)255, (unsigned char)0,(unsigned char)255,
        (unsigned char)0, (unsigned char)0, (unsigned char)255,(unsigned char)255,          (unsigned char)0, (unsigned char)0, (unsigned char)0,(unsigned char)255
    };

    Texture* texture = new Texture();
    texture->data = picture;
    texture->width = 2;
    texture->height = 2;
    
    EXPECT_EQ(texture->data[0], (unsigned char)255);
    EXPECT_EQ(texture->data[1], (unsigned char)0);
    EXPECT_EQ(texture->data[3], (unsigned char)255);
    EXPECT_EQ(texture->data[2], (unsigned char)0);

    EXPECT_EQ(texture->data[4], (unsigned char)0);
    EXPECT_EQ(texture->data[5], (unsigned char)255);
    EXPECT_EQ(texture->data[6], (unsigned char)0);
    EXPECT_EQ(texture->data[7], (unsigned char)255);

    EXPECT_EQ(texture->data[8], (unsigned char)0 );
    EXPECT_EQ(texture->data[9], (unsigned char)0);
    EXPECT_EQ(texture->data[10], (unsigned char)255);
    EXPECT_EQ(texture->data[11], (unsigned char)255);

    EXPECT_EQ(texture->data[12], (unsigned char)0);
    EXPECT_EQ(texture->data[13], (unsigned char)0);
    EXPECT_EQ(texture->data[14], (unsigned char)0);
    EXPECT_EQ(texture->data[15], (unsigned char)255);

    Texture::flipYAxis(texture);

    EXPECT_EQ(texture->data[0], (unsigned char)0);
    EXPECT_EQ(texture->data[1], (unsigned char)0);
    EXPECT_EQ(texture->data[2], (unsigned char)255);
    EXPECT_EQ(texture->data[3], (unsigned char)255);

    EXPECT_EQ(texture->data[4], (unsigned char)0);
    EXPECT_EQ(texture->data[5], (unsigned char)0);
    EXPECT_EQ(texture->data[6], (unsigned char)0);
    EXPECT_EQ(texture->data[7], (unsigned char)255);

    EXPECT_EQ(texture->data[8], (unsigned char)255);
    EXPECT_EQ(texture->data[9], (unsigned char)0);
    EXPECT_EQ(texture->data[10], (unsigned char)0);
    EXPECT_EQ(texture->data[11], (unsigned char)255);

    EXPECT_EQ(texture->data[12], (unsigned char)0);
    EXPECT_EQ(texture->data[13], (unsigned char)255);
    EXPECT_EQ(texture->data[14], (unsigned char)0);
    EXPECT_EQ(texture->data[15], (unsigned char)255);

}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}