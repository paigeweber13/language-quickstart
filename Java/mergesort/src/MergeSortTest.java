import org.junit.Test;
import org.junit.jupiter.api.DisplayName;

import static org.junit.jupiter.api.Assertions.*;

class MergeSortTest {

    @Test
    @DisplayName("Successfully creates an array.")
    public void testCreateArray() {
        int[] arrTest10 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        assertArrayEquals(arrTest10, MergeSort.createArray(10));
    }

}