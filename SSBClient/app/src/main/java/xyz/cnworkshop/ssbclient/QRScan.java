
package xyz.cnworkshop.ssbclient;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;

import java.util.ArrayList;
import java.util.List;

import cn.bingoogolapple.qrcode.core.BarcodeType;
import cn.bingoogolapple.qrcode.core.QRCodeView;
import cn.bingoogolapple.qrcode.zbar.BarcodeFormat;
import cn.bingoogolapple.qrcode.zbar.ZBarView;

public class QRScan extends AppCompatActivity implements QRCodeView.Delegate {
    private static final String TAG = QRScan.class.getSimpleName();

    private ZBarView mZBarView;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_qrscan);
        setSupportActionBar((Toolbar) findViewById(R.id.toolbar));
        mZBarView = findViewById(R.id.zbarview);
        mZBarView.setDelegate(this);
    }
    private void setData(String scanRes){
        Intent data = new Intent();
        data.setData(Uri.parse(scanRes));
        setResult(RESULT_OK, data);
        finish();
    }

    @Override
    protected void onStart() {
        super.onStart();
        mZBarView.startCamera();
        mZBarView.startSpotAndShowRect();
    }

    @Override
    protected void onStop() {
        mZBarView.stopCamera(); // 关闭摄像头预览，并且隐藏扫描框
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        mZBarView.onDestroy(); // 销毁二维码扫描控件
        super.onDestroy();
    }

    @Override
    public void onScanQRCodeSuccess(String result) {
        Log.i(TAG, "result:" + result);
        setTitle("扫描结果为：" + result);
        setData(result);
        mZBarView.startSpot(); // 开始识别
    }

    @Override
    public void onCameraAmbientBrightnessChanged(boolean isDark) {
        // 这里是通过修改提示文案来展示环境是否过暗的状态，接入方也可以根据 isDark 的值来实现其他交互效果
        String tipText = mZBarView.getScanBoxView().getTipText();
        String ambientBrightnessTip = "\n环境过暗，请打开闪光灯";
        if (isDark) {
            if (!tipText.contains(ambientBrightnessTip)) {
                mZBarView.getScanBoxView().setTipText(tipText + ambientBrightnessTip);
            }
        } else {
            if (tipText.contains(ambientBrightnessTip)) {
                tipText = tipText.substring(0, tipText.indexOf(ambientBrightnessTip));
                mZBarView.getScanBoxView().setTipText(tipText);
            }
        }
    }

    @Override
    public void onScanQRCodeOpenCameraError() {
        Log.e(TAG, "打开相机出错");
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.start_preview:
                mZBarView.startCamera(); // 打开后置摄像头开始预览，但是并未开始识别
                break;
            case R.id.stop_preview:
                mZBarView.stopCamera(); // 关闭摄像头预览，并且隐藏扫描框
                break;
            case R.id.start_spot:
                mZBarView.startSpot(); // 开始识别
                break;
            case R.id.stop_spot:
                mZBarView.stopSpot(); // 停止识别
                break;
            case R.id.start_spot_showrect:
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.stop_spot_hiddenrect:
                mZBarView.stopSpotAndHiddenRect(); // 停止识别，并且隐藏扫描框
                break;
            case R.id.show_scan_rect:
                mZBarView.showScanRect(); // 显示扫描框
                break;
            case R.id.hidden_scan_rect:
                mZBarView.hiddenScanRect(); // 隐藏扫描框
                break;
            case R.id.decode_scan_box_area:
                mZBarView.getScanBoxView().setOnlyDecodeScanBoxArea(true); // 仅识别扫描框中的码
                break;
            case R.id.decode_full_screen_area:
                mZBarView.getScanBoxView().setOnlyDecodeScanBoxArea(false); // 识别整个屏幕中的码
                break;
            case R.id.open_flashlight:
                mZBarView.openFlashlight(); // 打开闪光灯
                break;
            case R.id.close_flashlight:
                mZBarView.closeFlashlight(); // 关闭闪光灯
                break;
            case R.id.scan_one_dimension:
                mZBarView.changeToScanBarcodeStyle(); // 切换成扫描条码样式
                mZBarView.setType(BarcodeType.ONE_DIMENSION, null); // 只识别一维条码
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_two_dimension:
                mZBarView.changeToScanQRCodeStyle(); // 切换成扫描二维码样式
                mZBarView.setType(BarcodeType.TWO_DIMENSION, null); // 只识别二维条码
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_qr_code:
                mZBarView.changeToScanQRCodeStyle(); // 切换成扫描二维码样式
                mZBarView.setType(BarcodeType.ONLY_QR_CODE, null); // 只识别 QR_CODE
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_code128:
                mZBarView.changeToScanBarcodeStyle(); // 切换成扫描条码样式
                mZBarView.setType(BarcodeType.ONLY_CODE_128, null); // 只识别 CODE_128
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_ean13:
                mZBarView.changeToScanBarcodeStyle(); // 切换成扫描条码样式
                mZBarView.setType(BarcodeType.ONLY_EAN_13, null); // 只识别 EAN_13
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_high_frequency:
                mZBarView.changeToScanQRCodeStyle(); // 切换成扫描二维码样式
                mZBarView.setType(BarcodeType.HIGH_FREQUENCY, null); // 只识别高频率格式，包括 QR_CODE、ISBN13、UPC_A、EAN_13、CODE_128
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_all:
                mZBarView.changeToScanQRCodeStyle(); // 切换成扫描二维码样式
                mZBarView.setType(BarcodeType.ALL, null); // 识别所有类型的码
                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;
            case R.id.scan_custom:
                mZBarView.changeToScanQRCodeStyle(); // 切换成扫描二维码样式

                List<BarcodeFormat> formatList = new ArrayList<>();
                formatList.add(BarcodeFormat.QRCODE);
                formatList.add(BarcodeFormat.ISBN13);
                formatList.add(BarcodeFormat.UPCA);
                formatList.add(BarcodeFormat.EAN13);
                formatList.add(BarcodeFormat.CODE128);
                mZBarView.setType(BarcodeType.CUSTOM, formatList); // 自定义识别的类型

                mZBarView.startSpotAndShowRect(); // 显示扫描框，并开始识别
                break;

        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mZBarView.showScanRect();
    }

}