package com.example.druggist.rpncalculator

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.Button
import kotlinx.android.synthetic.main.activity_calculator.*
import kotlin.math.pow
import kotlin.math.sqrt
import kotlin.math.log

class CalculatorActivity : AppCompatActivity() {
    private var segments = mutableListOf<String>("")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_calculator)
        setSupportActionBar(findViewById(R.id.action_bar))
        printVal()
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.action_bar, menu)
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem) = when (item.itemId) {
        R.id.action_settings -> {
            val intent = Intent(this, SettingsActivity::class.java).apply {  }
            startActivity(intent)
            true
        }
        else -> {
            super.onOptionsItemSelected(item)
        }
    }

    private fun printVal() {
        segment1.text = segments[0]
        if(segments.size > 3) {
            segment2.text = segments[1]
            segment3.text = segments[2]
            segment4.text = segments[3]
        } else if (segments.size > 2) {
            segment2.text = segments[1]
            segment3.text = segments[2]
            segment4.text = ""
        } else if (segments.size > 1) {
            segment2.text = segments[1]
            segment3.text = ""
            segment4.text = ""
        } else {
            segment2.text = ""
            segment3.text = ""
            segment4.text = ""
        }
    }

    fun appendChar(view: View) {
        val b = view as Button
        var str = b.text
        if (str == ".") {
            if(segments[0].contains(".")) return
            if(segments[0].isEmpty()) str = "0."
        }
        if(str == "0" && segments[0] == "0") return
        segments[0] = segments[0] + str
        printVal()
    }

    fun enterAction(view: View) {
        if(segments[0].isNotBlank()) {
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments.add(0, "")
        }
        printVal()
    }

    fun swapAction(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank()) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            val tmp = segments[0]
            segments[0] = segments[1]
            segments[1] = tmp
        }
        printVal()
    }

    fun dropAction(view: View) {
        if(segments.size > 1) segments.removeAt(0)
        else segments[0] = ""
        printVal()
    }

    fun allClearAction(view: View) {
        segments.clear()
        segments.add("")
        printVal()
    }

    fun addCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank()) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = (segments[1].toDouble() + segments[0].toDouble()).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun subtractCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank()) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = (segments[1].toDouble() - segments[0].toDouble()).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun multiplyCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank()) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = (segments[1].toDouble() * segments[0].toDouble()).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun divideCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank() && segments[0].toDouble() != 0.0) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = (segments[1].toDouble() / segments[0].toDouble()).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun powCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank()) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = (segments[1].toDouble().pow(segments[0].toDouble())).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun sqrtCalc(view: View) {
        if(segments[0].isNotBlank() && segments[0].toDouble() >= 0.0) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = sqrt(segments[0].toDouble()).toString()
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun logCalc(view: View) {
        if(segments.size > 1 && segments[0].isNotBlank() && segments[1].toDouble() > 0.0  && segments[0].toDouble() > 0.0  && segments[1].toDouble() != 1.0) {
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments[0] = log(segments[0].toDouble(), segments[1].toDouble()).toString()
            segments.removeAt(1)
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
        }
        printVal()
    }

    fun signChangeAction(view: View) {
        if (segments[0].isNotBlank()) {
            if(segments[0].startsWith("-")) segments[0] = segments[0].substringAfter("-")
            else segments[0] = "-" + segments[0]
        }
        printVal()
    }

    fun undoAction(view: View) {
        if(segments[0].isNotBlank()) {
            if(segments[0].length > 1) segments[0] = segments[0].substring(0, segments[0].length - 1)
            else segments[0] = ""
        } else dropAction(view)
        printVal()
    }
}
