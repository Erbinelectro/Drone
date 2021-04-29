#ifndef _MPU9250_I2C_H_
#define _MPU9250_I2C_H_

#define MPU9250_SLAVE_ADDR_LOW (0b1101000 << 1)//AD0 == LOW
#define MPU9250_SLAVE_ADDR_HIGH (0b1101001 << 1)//AD0 == HIGH
#define MPU9250_MAG_ADDR (0b0001100 << 1)

#define MPU9250_WRITE_FLAG 0b00000000
#define MPU9250_READ_FLAG  0b00000001
#define MPU9250_CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG2 0x1D
#define LP_ACCEL_ODR 0x1E
#define INT_PIN_CFG 0x37
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCLE_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define MPU9250_TEMP_OUT_H 0x41
#define MPU9250_TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define WHO_AM_I_MPU9250 0x75 //0x71�Ȃ炨��
#define XG_OFFSET_H 0x13
#define XG_OFFSET_L 0x14
#define YG_OFFSET_H 0x15
#define YG_OFFSET_L 0x16
#define ZG_OFFSET_H 0x17
#define ZG_OFFSET_L 0x18
#define XA_OFFSET_H 0x77
#define XA_OFFSET_L 0x78
#define YA_OFFSET_H 0x79
#define YA_OFFERT_L 0x80
#define ZA_OFFSET_H 0x81
#define ZA_OFFSET_L 0x82

#define MPU9250_WIA 0x00 //device ID
#define MPU9250_INFO 0x01
#define MPU9250_ST1 0x02
#define HXL 0x03//Low -> High�̏��ɒ���
#define MPU9250_HXH 0x04
#define MPU9250_HYL 0x05
#define MPU9250_HYH 0x06
#define MPU9250_HZL 0x07
#define MPU9250_HZH 0x08
#define MPU9250_ST2 0x09
#define MPU9250_CNTL1 0x0A
#define MPU9250_CNTL2 0x0B

#define ACC_LSB (0.0000610350f)//[G / LSB]
#define GYRO_LSB (0.007630f) //[(degree / s) / LSB]
#define MPU9250_MAG_LSB (0.150f) //[uT / LSB]

typedef enum AD0 {
    AD0_HIGH = 1,
    AD0_LOW = 0
} ad0;

typedef enum ACC_RANGE {
    _2G = 1,
    _4G = 2,
    _8G = 4,
    _16G = 8
} acc_range;

typedef enum GYRO_RANGE {
    _250DPS = 1,
    _500DPS = 2,
    _1000DPS = 4,
    _2000DPS = 8
} gyro_range;

typedef enum MAG_RATE {
    _8HZ = 0,
    _100HZ = 1
} mag_rate;

typedef enum A_BAND_WIDTH {
    NO_USE = 0b00000000,
    _460HZ = 0b00001000,
    _184HZ = 0b00001001,
    _92HZ = 0b00001010,
    _41HZ = 0b00001011,
    _20HZ = 0b00001100,
    _10HZ = 0b00001101,
    _5HZ = 0b00001110,
} a_band_width;

/**
*  @bref  mpu9250���r�I�ȒP�ɗ��p�ł���悤�ɂ������C�u����
*  @note  ���[�p�X�t�B���^�܂��̎������܂��ł��D ������AK8963�̓X���[�u�A�h���X�Œ�Ȃ̂ŁC���������ł͎g�p�ł��܂���D
*  @author  Gaku MATSUMOTO
*/
class mpu9250
{

public:

    /**
    *  @bref  mpu9250�C���X�^���X�𐶐�����
    *  @param  _i2c  ���C���v���O�����Ő錾����I2C�C���X�^���X�̃A�h���X
    *  @param  celect  AD0�s����HIGH�Ȃ�AD0_HIGH�CLOW�Ȃ�AD0_LOW
    *  @note  �������Ȃ�����AD0_HIGH�ɂȂ�܂��D
    */
    mpu9250(I2C& _i2c, AD0 celect = AD0_HIGH);

    I2C* _nine;
public:
    void writeReg(char addr, char data);
    void writeReg(char addr, char reg, char data);
    char readReg(char addr, char reg);
    void readReg(char addr, char start_reg, char* buff, char num);

    /*!
     @bref  �����Z���T�ƒʐM���ł��Ă��邩�m�F����
     @note  true���Ԃ��Ă����琬���Cfalse�Ȃ�D�D�D
     */
    bool sensorTest();

    /**
    * @fn bool mpu9250::mag_senserTest()
    * @bref �n���C�Z���T�ƒʐM���ł��Ă��邩�m�F����
    * @note true���Ԃ��Ă����琬���Cfalse�Ȃ�D�D�D
    */
    bool mag_sensorTest();

    /**
     *    @bref  �����x�Z���T�̃����W��ݒ�
     *    @param  a_range _2G, _4G, _8G, _16G�̒�����I��
     *    @note  ���������Ł}4G�ɂȂ�
     */
    void setAcc(ACC_RANGE a_range = _4G);

    /**
     *    @bref  �p���x�Z���T�̃����W�ݒ�
     *    @param  g_range _250DPS, _500DPS, _1000DPS, _2000DPS�̒�����I��
     *    @note  ���������Ł}500DPS
     */
    void setGyro(GYRO_RANGE g_range = _500DPS);

    /**
     *    @bref  �n���C�Z���T�̃f�[�^���[�g�ݒ�
     *    @param  rate  _8HZ �� _100HZ��I��
     *    @note  ������8Hz�ɂ���K�v�͖����Ǝv���܂��D
     */
     //void setMag(MAG_RATE rate = _100HZ);

private:
    void init();

public:
    /**
     *    @bref   I2C�̒ʐM���x��ύX�ł��܂��D�]���̂��Ƃ��Ȃ�����g�p���Ȃ��Ă����ł��E
     */
    void frequency(int Hz);

    /**
     *    @bref  mpu9250�̃f�W�^�����[�p�X�t�B���^�̐ݒ�
     *    @param  band  NO_USE, _460HZ, _184HZ, _92HZ, _41HZ, _20HZ, _10HZ, _5HZ����I��
     *    @note  �J�b�g�I�t���g���Ȃ̂��T���v�����[�g�Ȃ̂��悭������܂���D�������ʂ������܂���
     */
    void setAccLPF(A_BAND_WIDTH band);

    /**
     *    @bref  �[���_�̂����␳����I�t�Z�b�g�l��ݒ肷��
     *    @param  ax,ay,az    �����x�̃I�t�Z�b�g
     *    @param  gx,gy,gz    �p���x�̃I�t�Z�b�g
     *    @param  mx,my,mz    �n���C�̃I�t�Z�b�g
     *    @note  �ƂĂ��d�v�ł��D�n���C�͒���I�ɃL�����u���[�V���������Ă��������D���Ȃ݂ɁC�����̒l�͑���l��������Ă��܂��D
     */
    void setOffset(float gx = 0.0f, float gy = 0.0f, float gz = 0.0f,
        float ax = 0.0f, float ay = 0.0f, float az = 0.0f,
        float mx = 0.0f, float my = 0.0f, float mz = 0.0f);

    /**
     *    @bref  �����x���擾���܂��D
     *    @param  ax  x�������̉����x[G]
     *    @param  ay  y�������̉����x[G]
     *    @param  az  z�������̉����x[G]
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getAcc(T* ax, T* ay, T* az);

    /**
     *    @bref  �����x���擾���܂��D
     *    @param  acc  �e�������̉����x[G]�Cx,y,z�̏�
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getAcc(T* acc);

    /**
     *    @bref  �p���x���擾���܂��D
     *    @param  gx  x�������̊p���x[degree/s]
     *    @param  gy  y�������̊p���x[degree/s]
     *    @param  gz  z�������̊p���x[degree/s]
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getGyro(T* gx, T* gy, T* gz);

    /**
     *    @bref  �p���x���擾���܂��D
     *    @param  gyro  �e�������̊p���x[degree/s], x,y,z�̏�
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getGyro(T* gyro);

    /**
     *    @bref  �������x���擾���܂��D
     *    @param  mx  x�������̎������x[uT]
     *    @param  my  y�������̎������x[uT]
     *    @param  mz  z�������̎������x[uT]
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getMag(T* mx, T* my, T* mz);


    /**
     *    @bref  �������x���擾���܂��D
     *    @param  mag  �e�������̎������x[uT]�Cx,y,z�̏�
     *    @note  �^��float �ł� double�ł��\���܂���D
     */
    template<typename T>void getMag(T* mag);

    /**
     *    @bref  �p���x�Ɖ����x�𓯎��Ɏ擾���܂��D
     *    @param  imu �f�[�^������z��C�p���x[degree/s],�����x[G]�̏�
     *    @note  �z�񐔂�6�ȏ��
     */
    template<typename T>void getGyroAcc(T* imu);//gx,gy,gz,ax,ay,az

    /**
     *    @bref  �p���x�Ɖ����x�ƒn���C�𓯎��Ɏ擾���܂��D
     *    @param imu �p���x�E�����x�f�[�^������z��C�p���x[degree/s],�����x[G]�̏�
     *    @param mag �n���C�f�[�^������z��
     *    @note  imu��6�Cmag��3�ȏ��
     */
    template<typename T>void getAll(T* imu, T* mag);

    /**
     *    @bref �p���x�Ɖ����x�ƒn���C�𓯎��Ɏ擾���܂��D
     *    @param all �p���x�E�����x�E�n���C�f�[�^������z��C�p���x[degree/s],�����x[G],�n���C[uT]�̏�
     *    @note  �v�f����9�ȏ�
     */
    template<typename T>void getAll(T* all);

private:
    char _addr;
    float acc_coef;//coefficient
    float gyro_coef;
    float mag_coef;
    float acc_offset[3];
    float gyro_offset[3];
    float mag_offset[3];
};



inline void mpu9250::writeReg(char addr, char data)
{
    _nine->write(addr | MPU9250_WRITE_FLAG, &data, 1, false);
}
inline void mpu9250::writeReg(char addr, char reg, char data)
{
    char temp[2] = { reg, data };
    _nine->write(addr | MPU9250_WRITE_FLAG, temp, 2, false);
}
inline char mpu9250::readReg(char addr, char reg)
{
    char buff[1];
    writeReg(addr, reg);
    _nine->read(addr | MPU9250_READ_FLAG, buff, 1, true);
    return buff[0];
}
inline void mpu9250::readReg(char addr, char start_reg, char* buff, char num)
{
    writeReg(addr, start_reg);
    _nine->read(addr | MPU9250_READ_FLAG, buff, num, true);
}

#endif