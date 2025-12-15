

int main() {

    Hash hash;
    hash.Update("Hello, world!");
    auto digest = hash.Digest();
    wxLogDebug(wxT("Контрольна сумма: %s"), digest);

}
