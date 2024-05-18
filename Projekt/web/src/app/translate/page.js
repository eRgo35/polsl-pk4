import styles from "../page.module.css";

import Header from "../components/Header";
import SideBar from "../components/SideBar";
import TranslateContent from "../components/TranslateContent";
import Footer from "../components/Footer";

export default function Home() {
  return (
    <main className={styles.main}>
      <Header title={"Machine Translation"} path={"translate"} />
      <SideBar />
      <TranslateContent />
      {/* <Footer /> */}
    </main>
  );
}
