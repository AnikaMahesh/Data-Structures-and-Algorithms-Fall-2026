import kotlin.math.*

fun iou(b1: List<Float>, b2: List<Float>): Float {
    if ((b1.size != 4) or (b2.size != 4)) {
        return 0.toFloat()
    }
    val ix1 = max(b1[0], b2[0])
    val iy1 = max(b1[1], b2[1])
    val ix2 = min(b1[2], b2[2])
    val iy2 = min(b1[3], b2[3])
    val inter = max(0.toFloat(), ix2-ix1) * max(0.toFloat(), iy2-iy1)
    val a1 = (b1[2]-b1[0]) * (b1[3]-b1[1])
    val a2 = (b2[2]-b2[0]) * (b2[3]-b2[1])
    val union = a1 + a2 - inter
    return if (union > 0) inter / union else 0.toFloat()
}

fun testIoU() {
    val tests = mutableListOf<Triple<List<Float>, List<Float>, Float>>()
    // Test 1: IoU of identical zero area boxes. Should be 0
    tests.add(Triple(listOf(1.toFloat(), 1.toFloat(), 1.toFloat(), 1.toFloat()), listOf(1.toFloat(), 1.toFloat(), 1.toFloat(), 1.toFloat()), 0.toFloat()))
    // Test 2: IoU of identical nonzero area boxes. Should be 1
    tests.add(Triple(listOf(0.1.toFloat(), 0.1.toFloat(), 0.3.toFloat(), 0.3.toFloat()), listOf(0.1.toFloat(), 0.1.toFloat(), 0.3.toFloat(), 0.3.toFloat()), 1.toFloat()))
    // Test 3: IoU of nonoverlapping boxes. Should be 0
    tests.add(Triple(listOf(0.1.toFloat(), 0.1.toFloat(), 0.3.toFloat(), 0.3.toFloat()), listOf(0.4.toFloat(), 0.4.toFloat(), 0.5.toFloat(), 0.5.toFloat()), 0.toFloat()))
    // Test 4: IoU of borderline nonoverlapping boxes. Should be 0
    tests.add(Triple(listOf(0.1.toFloat(), 0.1.toFloat(), 0.3.toFloat(), 0.3.toFloat()), listOf(0.3.toFloat(), 0.3.toFloat(), 0.5.toFloat(), 0.5.toFloat()), 0.toFloat()))
    // Test 5: IoU of overlapping rectangular boxes. Should be 0.14285
    tests.add(Triple(listOf(0.1.toFloat(), 0.1.toFloat(), 0.3.toFloat(), 0.3.toFloat()), listOf(0.2.toFloat(), 0.2.toFloat(), 0.4.toFloat(), 0.4.toFloat()), 0.14285.toFloat()))
    // Test 6: IoU of overlapping nonrectangular boxes. Should be 0.14285
    tests.add(Triple(listOf(0.1.toFloat(), 0.2.toFloat(), 0.3.toFloat(), 0.4.toFloat()), listOf(0.2.toFloat(), 0.3.toFloat(), 0.4.toFloat(), 0.5.toFloat()), 0.14285.toFloat()))
    // Test 7: IoU of overlapping boxes where one box is enclosed in another. Should be 0.0625
    tests.add(Triple(listOf(0.1.toFloat(), 0.1.toFloat(), 0.9.toFloat(), 0.9.toFloat()), listOf(0.2.toFloat(), 0.2.toFloat(), 0.4.toFloat(), 0.4.toFloat()), 0.0625.toFloat()))

    var testCount = 0
    var testsPassed = 0
    for ((b1,b2,truth) in tests) {
        testCount++
        val result = iou(b1,b2)
        if (abs(result - truth) < 0.00001) {
            testsPassed++
            println("IoU Test $testCount passed")
        }
        else {
            println("IoU test $testCount failed")
        }
    }
    println("$testsPassed tests passed out of $testCount tests")
}
