
fun checkMeetingConflictsBruteForce(meetingTimes : List<String>): Boolean {
    val meetingTimesList = mutableListOf<Pair<Float, Float>>()
    for (meeting in meetingTimes) {
        val meet = meeting.split("-")
        val end = meet[1].split(":")
        val start = meet[0].split(":")
        meetingTimesList.add(start[0].toInt() + start[1].toFloat() / 60 to end[0].toInt() + end[1].toFloat() / 60)
    }
    for ((first1, second1) in meetingTimesList) {
        for ((first, second) in meetingTimesList) {
            if (first1 > first && first1 < second || second1 > first && second1 < second) {
                return false
            }
        }
    }
    return true
}
fun checkMeetingConflictsEfficient(meetingTimes : List<String>): Boolean {
    var currentRunningMeetings: Int = 0
    // sort in ascending order
    val meetingTimesList = mutableListOf<Pair<Float, String>>()
    val starts = mutableListOf<Pair<Float, String>>()
    for (meeting in meetingTimes) {
        val meet = meeting.split("-")
        val end = meet[1].split(":")
        val start = meet[0].split(":")
        starts.add(start[0].toInt() + start[1].toFloat() / 60 to "start")
        meetingTimesList.add(end[0].toInt() + end[1].toFloat() / 60 to "end")
    }
    meetingTimesList.addAll(starts)
    meetingTimesList.sortBy { it.first }
    // go through sorted list. every time a meeting states add one to current meetings when a meeting ends subtract one
    val maxRunningMeetings: Int = 1
    for ((_, second) in meetingTimesList) {
        if (second == "end") {
            currentRunningMeetings -= 1
        } else {
            currentRunningMeetings += 1
        }
        if (currentRunningMeetings > maxRunningMeetings) {
            return false
        }
    }
    return true
}
fun testMeetingTimes() {
    val meetingTimes: List<String> = listOf("10:00-11:00", "10:30-10:40", "12:30-13:30", "13:30-14:00")
    val efficient = checkMeetingConflictsEfficient(meetingTimes)
    val bruteforce = checkMeetingConflictsBruteForce(meetingTimes)
    println("efficient $efficient")
    println("brute force $bruteforce")
    // Unit Tests
    // Test with conflicting meetings when one encapsulates the other: Expected: false
    val test1: Pair<List<String>, Boolean> = listOf("10:00-11:00", "10:30-10:40") to false
    // Tests with conflicting meetings when one is partially overlapped by the other: Expected: false
    // Checks when 2nd meeting starts when first has already started: Expected: false
    val test2: Pair<List<String>, Boolean> = listOf("10:00-11:00", "10:30-11:40") to false
    // Checks when 2nd meeting ends after first has started: Expected: false
    val test3: Pair<List<String>, Boolean> = listOf("10:40-12:00", "10:30-11:40") to false
    // Tests with non-conflicting meetings: Expected: true
    val test4: Pair<List<String>, Boolean> = listOf("9:40-10:00", "10:30-11:40", "11:50-12:00", "12:30-13:30", "14:00-17:00") to true
    // Tests with non-conflicting back to back meetings: Expected: true
    val test5: Pair<List<String>, Boolean> = listOf("9:40-10:00", "10:00-11:40", "11:40-12:00", "12:00-13:30", "13:30-17:00") to true
    // Tests with non-conflicting back to back meetings not in ascending order: Expected: true
    val test6: Pair<List<String>, Boolean> = listOf( "13:30-17:00", "12:00-13:30","11:40-12:00", "10:00-11:40", "9:40-10:00") to true
    // Tests with 1 conflicting meeting at the end of the list: Expected: false
    val test7: Pair<List<String>, Boolean> = listOf( "9:40-10:00", "10:30-11:40", "11:50-12:00", "12:30-14:30", "14:00-17:00") to false
    // Tests with 3 conflicting meetings: Expected: false
    val test8: Pair<List<String>, Boolean> = listOf( "9:40-10:00", "10:30-11:40", "11:50-16:00", "12:30-14:30", "14:00-17:00") to false

    val tests = listOf(test1, test2, test3, test4, test5, test6, test7, test8, test8)

    var testCount = 0
    var bruteforceTestPassCount = 0
    var efficientTestPassCount = 0
    for ((test, result) in tests) {
        testCount += 1
        val efficient = checkMeetingConflictsEfficient(test) == result
        val bruteforce = checkMeetingConflictsBruteForce(test) == result
        println("Brute Force Conflict Finder Test $testCount Pass: $bruteforce")
        println("Efficient Conflict Finder Test $testCount Pass: $efficient")
        bruteforceTestPassCount += if (bruteforce) 1 else 0
        efficientTestPassCount += if (efficient) 1 else 0
    }
    println("bruteforce passed $bruteforceTestPassCount tests out of $testCount")
    println("efficient passed $efficientTestPassCount tests out of $testCount")
}
