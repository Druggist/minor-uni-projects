package com.example.druggist.rpncalculator

import android.app.Activity
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
    val REQUEST_CODE = 1000
    private var segments = mutableListOf("")
    private var darkTheme = true
    private var precision = -1
    private var newLine = false

    override fun onCreate(savedInstanceState: Bundle?) {
        if (savedInstanceState != null) {
            with(savedInstanceState) {
                precision = getInt("Precision")
                darkTheme = getBoolean("DarkTheme")
                segments = getStringArrayList("Stack").toMutableList()
            }
        }

        setTheme(if(darkTheme) android.R.style.ThemeOverlay_Material_Dark else android.R.style.ThemeOverlay_Material_Light)

        setContentView(R.layout.activity_calculator)
        setSupportActionBar(findViewById(R.id.action_bar))
        printVal()
        super.onCreate(savedInstanceState)
    }

    override fun onSaveInstanceState(outState: Bundle?) {
        outState?.run {
            putInt("Precision", precision)
            putBoolean("DarkTheme", darkTheme)
            putStringArrayList("Stack", ArrayList(segments))
        }
        super.onSaveInstanceState(outState)
    }

    fun Double.format(digits: Int) = java.lang.String.format("%.${digits}f", this)

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.action_bar, menu)
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem) = when (item.itemId) {
        R.id.action_settings -> {
            val i = Intent(this, PreferencesActivity::class.java)
            i.putExtra("DarkTheme", darkTheme)
            i.putExtra("Precision", precision)
            startActivityForResult(i, REQUEST_CODE)
            true
        }
        else -> {
            super.onOptionsItemSelected(item)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if((requestCode == REQUEST_CODE) && (resultCode == Activity.RESULT_OK)) {
            if(data != null) {
                if(data.hasExtra("DarkTheme")) darkTheme = data.getBooleanExtra("DarkTheme", false)
                if(data.hasExtra("Precision")) precision = data.getIntExtra("Precision", -1)
            }
            recreate()
        }
    }

    private fun printVal() {
        segment1.text = segments[0]
        if(segments.size > 3) {
        if(precision > -1) {
            segment2.text = segments[1].toDouble().format(precision)
            segment3.text = segments[2].toDouble().format(precision)
            segment4.text = segments[3].toDouble().format(precision)
        } else {
            segment2.text = segments[1]
            segment3.text = segments[2]
            segment4.text = segments[3]
        }
        } else if (segments.size > 2) {
            if(precision > -1) {
                segment2.text = segments[1].toDouble().format(precision)
                segment3.text = segments[2].toDouble().format(precision)
            } else {
                segment2.text = segments[1]
                segment3.text = segments[2]
            }
            segment4.text = ""
        } else if (segments.size > 1) {
            segment2.text = if(precision <= -1) segments[1] else segments[1].toDouble().format(precision)
            segment3.text = ""
            segment4.text = ""
        } else {
            segment2.text = ""
            segment3.text = ""
            segment4.text = ""
        }
    }

    fun setEdit(setEdit: Boolean) {
        if(!setEdit) {
            label1.text = "1:"
            label2.text = "2:"
            label3.text = "3:"
            label4.text = "4:"
        } else {
            label1.text = "=>"
            label2.text = "1:"
            label3.text = "2:"
            label4.text = "3:"
        }
    }

    fun appendChar(view: View) {
        setEdit(true)
        if(!segments[0].isEmpty() && newLine) {
            if(segments[0].endsWith(".0")) segments[0] = segments[0].substringBefore(".0")
            if(segments[0].endsWith(".")) segments[0] = segments[0].substringBefore(".")
            segments.add(0, "")
            newLine = false
        }
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
            newLine = true
            setEdit(false)
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
        if(segments.size > 1) {
            segments.removeAt(0)
            newLine = true
        } else {
            segments[0] = ""
            newLine = false
        }
        setEdit(false)
        printVal()
    }

    fun allClearAction(view: View) {
        segments.clear()
        segments.add("")
        printVal()
        setEdit(false)
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
