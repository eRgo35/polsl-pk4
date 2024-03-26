import styles from "../page.module.css"

export default function SideBar() {
  return (
  <nav class="sidebar offcanvas-start offcanvas-md" tabindex="-1" id="sidebar-example">
    <div class="offcanvas-header">
      <a class="sidebar-brand" href="#">
        NLP Platform
      </a>
      <button type="button" class="btn-close d-md-none" data-bs-dismiss="offcanvas" aria-label="Close" data-bs-target="#sidebar-example"></button>
    </div>
    <div class="offcanvas-body">
      <div class="mt-2 mb-3">
        <input type="text" class="form-control" placeholder="Search" />
      </div>
      <ul class="sidebar-nav">
        <li>
          <h6 class="sidebar-header">Lorem ipsum</h6>
        </li>
        <li><hr class="sidebar-divider" /></li>
        <li class="nav-item">
          <a class="nav-link active" href="#" aria-current="page">dolor sit</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">consectetur adipiscing elit</a>
        </li>
        <li class="mt-3">
          <h6 class="sidebar-header">eiusmod tempor</h6>
        </li>
        <li><hr class="sidebar-divider" /></li>
        <li class="nav-item">
          <a class="nav-link" href="#">labore et dolore</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">magna aliqua</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">deserunt mollit</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">est laborum</a>
        </li>
      </ul>
    </div>
  </nav>
  );
}
