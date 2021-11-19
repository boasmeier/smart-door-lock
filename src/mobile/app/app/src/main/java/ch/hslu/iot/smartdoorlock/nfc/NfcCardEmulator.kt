package ch.hslu.iot.smartdoorlock.nfc

import android.nfc.cardemulation.HostApduService
import android.os.Bundle
import android.util.Log

class NfcCardEmulator : HostApduService() {
    var TAG = "NfcCardEmulator"
    override fun processCommandApdu(commandApdu: ByteArray, extras: Bundle?): ByteArray {
        Log.i(TAG, "received data $commandApdu")
        return ByteArray(0)
    }

    override fun onDeactivated(reason: Int) {
        Log.i(TAG, "onDeactivated reason: $reason")
    }
}