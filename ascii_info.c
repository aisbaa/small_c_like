bool isWhiteSpace(char character) {
  /*
   * acourding ascii table, all below space (including)
   * originally intended NOT to represent printable
   * information, so it might not be space, but it should
   * be white
   *
   * and 127 officialy is delete
   */
  return (character <= ' ' || character   == (char)127);
}
